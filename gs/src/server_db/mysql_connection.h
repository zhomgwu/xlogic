#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#include <string>

#include "noncopyable.h"
#include "mysql/mysql.h"

class mysql_connection : public noncopyable {
public:
    mysql_connection();
    ~mysql_connection();

public:
    // 连接数据库
    bool connect(const std::string& host, unsigned int port, 
        const std::string& user, const std::string& password, const std::string& db);
    // 断开连接
    bool close();
    // 查询,需要结合fetch_row来获得结果
    bool query(const std::string &statement);
    // 插入,返回auto_increment列生成的id
    int insert(const std::string &statement);
    // 改&删,返回影响的行数
    int modify(const std::string &statement);
    // 清空查询结构
    bool clear_res();
    // 转义查询语句中的特殊字符
    bool escape_string(char* dst, const char* src, int len);
    // 上次查询行数
    int num_rows();
    // 上次结果的列数
    int num_fields();
    // 获得当前行
    MYSQL_ROW fetch_row();
    // 返回当前行所有中列的数据长度
    unsigned long* fetch_lengths();

private:
    MYSQL*          m_mysql;                    //mysql实例
    MYSQL_RES*      m_mysql_res;                //mysql结果
};

#endif //__MYSQL_CONNECTION_H__
