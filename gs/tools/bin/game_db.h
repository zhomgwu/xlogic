#pragma once
#include <string>
#include "mysql_connection.h"
#include "db_opr_base.h"

class db_opr_player : public db_opr_base
{
public:
	db_opr_player(mysql_connection* connection);
	~db_opr_player();

public:
	// '自增主键'
	void set_id(int32_t id);
	// '角色id'
	void set_player_id(int64_t player_id);
	// '名称'
	void set_name(std::string name);
	// '头像'
	void set_picture(std::string picture);
	// '势力'
	void set_faction(int32_t faction);
	// '性别'
	void set_sex(int32_t sex);
	// '职业'
	void set_prof(int32_t prof);
	// '等级'
	void set_level(int32_t level);
	// '经验'
	void set_exp(int32_t exp);
	// 'vip'
	void set_vip_level(int32_t vip_level);
	// '官职'
	void set_offical_pos(int32_t offical_pos);
	// '战力'
	void set_power(int32_t power);
	// '现金'
	void set_cash(int32_t cash);
	// '元宝'
	void set_gold(int32_t gold);
	// '铜币'
	void set_copper(int32_t copper);
	// '亲密空间id'
	void set_cp_zone_id(int32_t cp_zone_id);
	// '累计在线'
	void set_online_time(int32_t online_time);
	// '最近登录时间戳'
	void set_login_ts(int64_t login_ts);
	// '最近登出时间戳'
	void set_logout_ts(int64_t logout_ts);


	// '自增主键'
	int32_t get_id() const;
	// '角色id'
	int64_t get_player_id() const;
	// '名称'
	std::string get_name() const;
	// '头像'
	std::string get_picture() const;
	// '势力'
	int32_t get_faction() const;
	// '性别'
	int32_t get_sex() const;
	// '职业'
	int32_t get_prof() const;
	// '等级'
	int32_t get_level() const;
	// '经验'
	int32_t get_exp() const;
	// 'vip'
	int32_t get_vip_level() const;
	// '官职'
	int32_t get_offical_pos() const;
	// '战力'
	int32_t get_power() const;
	// '现金'
	int32_t get_cash() const;
	// '元宝'
	int32_t get_gold() const;
	// '铜币'
	int32_t get_copper() const;
	// '亲密空间id'
	int32_t get_cp_zone_id() const;
	// '累计在线'
	int32_t get_online_time() const;
	// '最近登录时间戳'
	int64_t get_login_ts() const;
	// '最近登出时间戳'
	int64_t get_logout_ts() const;


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
	db_pb_player m_pb_player;
};

		