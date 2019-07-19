#include "game_db.h"

db_opr_player::db_opr_player(mysql_connection* connection)
: db_opr_base(connection) {
}

db_opr_player::~db_opr_player(){
}

void db_opr_player::set_id(int32_tid) {
	m_pb_player.set_id(id);
}

void db_opr_player::set_player_id(int64_tplayer_id) {
	m_pb_player.set_player_id(player_id);
}

void db_opr_player::set_name(std::stringname) {
	m_pb_player.set_name(name);
}

void db_opr_player::set_picture(std::stringpicture) {
	m_pb_player.set_picture(picture);
}

void db_opr_player::set_faction(int32_tfaction) {
	m_pb_player.set_faction(faction);
}

void db_opr_player::set_sex(int32_tsex) {
	m_pb_player.set_sex(sex);
}

void db_opr_player::set_prof(int32_tprof) {
	m_pb_player.set_prof(prof);
}

void db_opr_player::set_level(int32_tlevel) {
	m_pb_player.set_level(level);
}

void db_opr_player::set_exp(int32_texp) {
	m_pb_player.set_exp(exp);
}

void db_opr_player::set_vip_level(int32_tvip_level) {
	m_pb_player.set_vip_level(vip_level);
}

void db_opr_player::set_offical_pos(int32_toffical_pos) {
	m_pb_player.set_offical_pos(offical_pos);
}

void db_opr_player::set_power(int32_tpower) {
	m_pb_player.set_power(power);
}

void db_opr_player::set_cash(int32_tcash) {
	m_pb_player.set_cash(cash);
}

void db_opr_player::set_gold(int32_tgold) {
	m_pb_player.set_gold(gold);
}

void db_opr_player::set_copper(int32_tcopper) {
	m_pb_player.set_copper(copper);
}

void db_opr_player::set_cp_zone_id(int32_tcp_zone_id) {
	m_pb_player.set_cp_zone_id(cp_zone_id);
}

void db_opr_player::set_online_time(int32_tonline_time) {
	m_pb_player.set_online_time(online_time);
}

void db_opr_player::set_login_ts(int64_tlogin_ts) {
	m_pb_player.set_login_ts(login_ts);
}

void db_opr_player::set_logout_ts(int64_tlogout_ts) {
	m_pb_player.set_logout_ts(logout_ts);
}



int32_t db_opr_player::get_id() const {
	return m_pb_player.id();
}

int64_t db_opr_player::get_player_id() const {
	return m_pb_player.player_id();
}

std::string db_opr_player::get_name() const {
	return m_pb_player.name();
}

std::string db_opr_player::get_picture() const {
	return m_pb_player.picture();
}

int32_t db_opr_player::get_faction() const {
	return m_pb_player.faction();
}

int32_t db_opr_player::get_sex() const {
	return m_pb_player.sex();
}

int32_t db_opr_player::get_prof() const {
	return m_pb_player.prof();
}

int32_t db_opr_player::get_level() const {
	return m_pb_player.level();
}

int32_t db_opr_player::get_exp() const {
	return m_pb_player.exp();
}

int32_t db_opr_player::get_vip_level() const {
	return m_pb_player.vip_level();
}

int32_t db_opr_player::get_offical_pos() const {
	return m_pb_player.offical_pos();
}

int32_t db_opr_player::get_power() const {
	return m_pb_player.power();
}

int32_t db_opr_player::get_cash() const {
	return m_pb_player.cash();
}

int32_t db_opr_player::get_gold() const {
	return m_pb_player.gold();
}

int32_t db_opr_player::get_copper() const {
	return m_pb_player.copper();
}

int32_t db_opr_player::get_cp_zone_id() const {
	return m_pb_player.cp_zone_id();
}

int32_t db_opr_player::get_online_time() const {
	return m_pb_player.online_time();
}

int64_t db_opr_player::get_login_ts() const {
	return m_pb_player.login_ts();
}

int64_t db_opr_player::get_logout_ts() const {
	return m_pb_player.logout_ts();
}


bool db_opr_player::parse_from_string(std::string &data) {
	return m_pb_player.ParseFromString(data);
}

bool db_opr_player::serialize_to_string(std::string &data) {
	return m_pb_player.SerializeToString(data);
}

::google::protobuf::Message* db_opr_player::get_message() {
	return &m_pb_player;
}

bool db_opr_player::read_from_res() {
	db_opr_player
	return false;
}

void db_opr_player::build_select_statment(std::string &statment) {
	db_opr_player
}

void db_opr_player::build_insert_statment(std::string &statment) {
	db_opr_player
}

void db_opr_player::build_update_statment(std::string &statment) {
	UPDATE player SET player_id=m_pb_player.player_id(), 
name=m_pb_player.name(), 
picture=m_pb_player.picture(), 
faction=m_pb_player.faction(), 
sex=m_pb_player.sex(), 
prof=m_pb_player.prof(), 
level=m_pb_player.level(), 
exp=m_pb_player.exp(), 
vip_level=m_pb_player.vip_level(), 
offical_pos=m_pb_player.offical_pos(), 
power=m_pb_player.power(), 
cash=m_pb_player.cash(), 
gold=m_pb_player.gold(), 
copper=m_pb_player.copper(), 
cp_zone_id=m_pb_player.cp_zone_id(), 
online_time=m_pb_player.online_time(), 
login_ts=m_pb_player.login_ts(), 
logout_ts=m_pb_player.logout_ts(), 
WHERE id=m_pb_player.id()
}

void db_opr_player::build_delete_statment(std::string &statment) {
	db_opr_player
}

void db_opr_player::build_insert_or_update_statment(std::string &statment) {
	db_opr_player
}

		