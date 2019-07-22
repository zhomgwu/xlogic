
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>


std::string replace_string(std::string& strSource, const std::string& strRepl, const std::string& strNew)
{
	std::string::size_type pos = 0;
	while ((pos = strSource.find(strRepl, pos)) != std::string::npos)
	{
		strSource.replace(pos, strRepl.length(), strNew);
		pos += strNew.length();
	}
	return strSource;
}

inline std::vector<std::string> split_string(const std::string & str, const std::string & delimiters)
{
	std::vector<std::string> v;
	std::string::size_type start = 0;
	auto pos = str.find_first_of(delimiters, start);
	while (pos != std::string::npos)
	{
		if (pos != start) // ignore empty tokens
			v.emplace_back(str, start, pos - start);
		start = pos + 1;
		pos = str.find_first_of(delimiters, start);
	}
	if (start < str.length()) // ignore trailing delimiter
		v.emplace_back(str, start, str.length() - start); // add what's left of the string
	return v;
}

struct field_type_t
{
	std::string field_name;
	std::string field_type;
	std::string field_comment;
};

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "sql2game [in_file_name] [out_dir] [out_file_name]" << std::endl;
		return 0;
	}

	std::string in_file_name{ argv[1] };
	std::string out_dir{ argv[2] };
	std::string out_file_name{ argv[3] };


	std::ifstream input_file(in_file_name);
	if (input_file.is_open() == false)
	{
		std::cout << in_file_name << "open fail" << std::endl;
		return false;
	}
	std::string input_string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	
	std::string output_header;
	std::string output_cpp;
	std::string output_proto;
	//将输入按;进行分割
	auto vecString = split_string(input_string, ";");
	for (auto& v : vecString)
	{
		std::cout << "string1:" << v << std::endl;
		
		std::string regextxt = R"(CREATE TABLE `(.*)` .*\(([\s\S]*)\) ENGINE.*=.*InnoDB (.*))";
		std::smatch base_match;
		if (std::regex_search(v, base_match, std::regex(regextxt)))
		{
			std::string table_name = base_match[1];
			std::string content = base_match[2];
			auto vecStr = split_string(content, "\n");
			std::vector< field_type_t > vecFieldType;
			std::unordered_set< std::string > PriKeys;

			std::vector<std::string> hub_field_types;
			std::vector<std::string> hub_field_names;

			for (auto& v : vecStr)
			{
				std::smatch field_match;
				if (std::regex_search(v, field_match, std::regex{ R"(.*PRIMARY KEY \((.*)\).*)" }))
				{
					std::string prikey_str = field_match[1];
					replace_string(prikey_str, "`", "");
					auto prikeys = split_string(prikey_str, ",");
					for (auto v : prikeys)
					{
						PriKeys.insert(v);
					}					
				}
				else if (std::regex_search(v, field_match, std::regex{ R"(.*`(.*)` (.*) NOT NULL.*COMMENT ('.*').*)" }))
				{
					std::string field_name = field_match[1];
					std::string field_type = field_match[2];
					std::string field_comment = field_match[3];
					vecFieldType.push_back({ field_name, field_type, field_comment});
				}
			}


			std::string fields_name;
			std::string fields_enum_list;
			std::string fields_type;
			std::string fields_type_enum;
			std::string is_pri_key_list;


			std::string class_name = "db_opr_" + table_name;
			std::string proto_class_name = "db_pb_" + table_name;
			std::string data_member = "m_pb_" + table_name;
			std::string set_functions;
			std::string get_functions;
			std::string cpp_set_functions;
			std::string cpp_get_functions;

			std::string select_statment;
			std::string insert_statment;
			std::string update_statment;
			std::string delete_statment;
			std::string update_or_insert_statment;

			for (unsigned int i = 0; i < vecFieldType.size(); i++)
			{
				const auto& v = vecFieldType[i];
				std::smatch field_match;
				if (v.field_name.empty() == false)
				{
					std::string field_name_UP = v.field_name;
					std::transform(field_name_UP.begin(), field_name_UP.end(), field_name_UP.begin(), ::toupper);

					if (std::regex_search(v.field_type, field_match, std::regex{ R"((.*)\((.*)\)(.*))" }))
					{
						std::string field_type = field_match[1];
						std::string field_bits = field_match[2];
						bool bUnsigned = field_match.size() > 2 && field_match[3] == " unsigned";
						std::string field_type_cpp;
						std::string field_type_proto;
						bool is_proto_type = false;
						if (field_type == "bigint")
						{
							if (bUnsigned)
							{
								field_type_cpp = "uint64_t";
								field_type_proto = "uint64";
							}
							else
							{
								field_type_cpp = "int64_t";
								field_type_proto = "int64";
							}
						}
						else if (field_type == "int")
						{
							if (bUnsigned)
							{
								field_type_cpp = "uint32_t";
								field_type_proto = "uint32";
							}
							else
							{
								field_type_cpp = "int32_t";
								field_type_proto = "int32";
							}
						}
						else if (field_type == "smallint")
						{
							if (bUnsigned)
							{
								field_type_cpp = "uint16_t";
								field_type_proto = "uint32";
							}
							else
							{
								field_type_cpp = "int16_t";
								field_type_proto = "int32";
							}
						}
						else if (field_type == "tinyint")
						{
							if (bUnsigned)
							{
								field_type_cpp = "uint8_t";
								field_type_proto = "uint32";
							}
							else
							{
								field_type_cpp = "int8_t ";
								field_type_proto = "int32";
							}
						}
						else if (field_type == "float")
						{
							field_type_cpp = "float";
							field_type_proto = "float";
						}
						else if (field_type == "double")
						{
							field_type_cpp = "double";
							field_type_proto = "double";
						}
						else if (field_type == "varchar")
						{
							// if (field_bits.empty())
							// {
							// 	field_type_cpp = "std::string ";
							// }
							// else
							// {
							// 	field_type_cpp = "char[" + field_bits + "] ";
							// }
							field_type_cpp = "std::string";
							field_type_proto = "string";
						}
						else if (field_type == "tinyblob" 
							|| field_type == "mediumblob"
							|| field_type == "blob"
							|| field_type == "longblob") {
							
							if (v.field_comment.empty()) {
								field_type_cpp = "std::string";	
								field_type_proto = "string";
							}
							else{
								is_proto_type = true;
								field_type_cpp = v.field_comment;	
								field_type_proto = v.field_comment;
								replace_string(field_type_cpp, "'", "");
								replace_string(field_type_proto, "'", "");
							}
						}

						hub_field_types.push_back(field_type_cpp);
						hub_field_names.push_back(v.field_name);

						if (is_proto_type) {
							// 设置函数
							set_functions += "\t// " + v.field_comment + "\n";
							set_functions += "\tvoid set_" + v.field_name + "(" + field_type_cpp + " &" + v.field_name + ");\n";
							// 获得函数
							get_functions += "\t// " + v.field_comment + "\n";
							get_functions += "\t void get_" + v.field_name + "(" + field_type_cpp + " &" + v.field_name + ") const;\n";
							// cpp 设置函数
							cpp_set_functions += "void "+ class_name+"::set_"+v.field_name + "(" + field_type_cpp /*+ " "*/ + v.field_name + ") {\n";
							cpp_set_functions += "\t"+ data_member + ".mutable_" + v.field_name +"()->CopyFrom("+v.field_name+");\n";
							cpp_set_functions += "}\n\n";
							// cpp 获取函数
							cpp_get_functions += "void "+ class_name +"::get_" + v.field_name + "(" + field_type_cpp + " &" + v.field_name + ") const {\n";
							cpp_get_functions += v.field_name + ".CopyFrom(" + data_member + "." + v.field_name + "());\n";
							cpp_get_functions += "}\n\n";	
						}
						else {
							// 设置函数
							set_functions += "\t// " + v.field_comment + "\n";
							set_functions += "\tvoid set_" + v.field_name + "(" + field_type_cpp + " " + v.field_name + ");\n";
							// 获得函数
							get_functions += "\t// " + v.field_comment + "\n";
							get_functions += "\t" + field_type_cpp + " get_" + v.field_name + "() const;\n";

							cpp_set_functions += "void "+ class_name+"::set_"+v.field_name + "(" + field_type_cpp /*+ " "*/ + v.field_name + ") {\n";
							cpp_set_functions += "\t"+ data_member + ".set_" + v.field_name +"("+v.field_name+");\n";
							cpp_set_functions += "}\n\n";

							cpp_get_functions += field_type_cpp + " " + class_name+"::get_"+v.field_name+"() const {\n";
							cpp_get_functions += "\treturn "+ data_member + "." + v.field_name +"();\n";
							cpp_get_functions += "}\n\n";
						}
					}				
				}
			}


			std::string output_format = R"(
class ${class_name} : public db_opr_base
{
public:
	${class_name}(mysql_connection* connection);
	~${class_name}();

public:
%s

%s

	bool parse_from_string(std::string &data);
	bool serialize_to_string(std::string &data);
	
	::google::protobuf::Message* get_message();

	virtual bool read_from_res() override;
	virtual void build_select_statment(std::string &statment) override;
	virtual void build_insert_statment(std::string &statment) override;
	virtual void build_update_statment(std::string &statment) override;
	virtual void build_delete_statment(std::string &statment) override;
	virtual void build_insert_or_update_statment(std::string &statment) override;

private:
	${proto_class_name} ${data_member};
};

		)";
			
			char szBuf[40960] = {};
			// std::string table_name_UP = table_name;
			// std::transform(table_name_UP.begin(), table_name_UP.end(), table_name_UP.begin(), ::toupper);
			replace_string(output_format, "${class_name}", class_name);
			replace_string(output_format, "${proto_class_name}", proto_class_name);
			replace_string(output_format, "${data_member}", data_member);
			sprintf(szBuf, output_format.c_str(), set_functions.c_str(), get_functions.c_str());
			output_header += szBuf;
			printf("%s", szBuf);


 			{
				std::string output_format = R"(
${class_name}::${class_name}(mysql_connection* connection)
: db_opr_base(connection) {
}

${class_name}::~${class_name}(){
}

%s

%s
bool ${class_name}::parse_from_string(std::string &data) {
	return ${data_member}.ParseFromString(data);
}

bool ${class_name}::serialize_to_string(std::string &data) {
	return ${data_member}.SerializeToString(data);
}

::google::protobuf::Message* ${class_name}::get_message() {
	return &${data_member};
}

bool ${class_name}::read_from_res() {
	%s
	return false;
}

void ${class_name}::build_select_statment(std::string &statment) {
	%s
}

void ${class_name}::build_insert_statment(std::string &statment) {
	%s
}

void ${class_name}::build_update_statment(std::string &statment) {
	%s
}

void ${class_name}::build_delete_statment(std::string &statment) {
	%s
}

void ${class_name}::build_insert_or_update_statment(std::string &statment) {
	%s
}

		)";

				auto build_readres_func = [&](std::vector<std::string>& field_types, std::vector<std::string>& field_names)->std::string {
					std::string code = "\n";
					

					return code;
				};

				auto build_update_func = [&](std::vector<std::string>& field_types, std::vector<std::string>& field_names)->std::string {
					std::string code = "statment = \"UPDATE " + table_name + " SET \"+\n";
					bool first = true;
					for (size_t i = 0; i < field_types.size(); ++i) {
						if (PriKeys.find(field_names[i]) != PriKeys.end()) {
							continue;
						}
						// 第一行不需要','号，看不懂代码因为是根据输出增删
						if (first) {
							first = false;
							code += "\t\"" + field_names[i] + "=\" + " + data_member + "." + field_names[i] + "()\n"; 	
						} else {
							code += "\t\", " + field_names[i] + "=\" + " + data_member + "." + field_names[i] + "()\n"; 	
						}
					}
					code += "\t+\" WHERE \"+";
					for (auto key : PriKeys) {
						code += "\"" + key +"=\" + "+data_member + "."+ key +"()";
					}
					code += ";";
					return code;
				};

				auto build_delete_func = [&]()->std::string {
					std::string code;
					code = "statment = \"DELETE FROM "+table_name;
					code += " WHERE \"+";
					bool first = true;
					for (auto key : PriKeys) {
						if (first) {
							first = false;
							code += "\"" + key +"=\" + "+data_member + "."+ key +"()";	
						} else {
							code += "\" AND " + key +"=\" + "+data_member + "."+ key +"()";	
						}						
					}
					code += ";";
					return code;
				};

				auto build_select_func = [&]() {
					std::string code;
					code = "select * from"
				};

				std::string updatestatment = build_update_func(hub_field_types, hub_field_names);
				std::string delstatment = build_delete_func();
				char szBuf[40960] = {};
				// std::string table_name_UP = table_name;
				// std::transform(table_name_UP.begin(), table_name_UP.end(), table_name_UP.begin(), ::toupper);
				replace_string(output_format, "${class_name}", class_name);
				replace_string(output_format, "${proto_class_name}", proto_class_name);
				replace_string(output_format, "${data_member}", data_member);
				sprintf(szBuf, output_format.c_str(), cpp_set_functions.c_str(), cpp_get_functions.c_str(),
				 	class_name.c_str(), class_name.c_str(), class_name.c_str(), updatestatment.c_str(), 
				 	delstatment.c_str(), class_name.c_str());
				output_cpp += szBuf;
				printf("%s", szBuf);
 			}
		}
	}
	

	{
		std::ofstream output_file(out_dir + out_file_name + ".h");
		output_file << "#pragma once\n";
		output_file << "#include <string>\n";
		output_file << "#include \"mysql_connection.h\"\n";
		output_file << "#include \"db_opr_base.h\"\n";
		output_file << output_header;
		output_file.close();
	}
	{
		std::ofstream output_file(out_dir + out_file_name + ".cpp");
		// output_file << "#include \"DBField.h\"\n";
		output_file << "#include \"" + out_file_name+ ".h\"\n";
		output_file << output_cpp;
		output_file.close();
	}
}
