#include "db_opr_base.h"

db_opr_base::db_opr_base(mysql_connection * connection)
: m_mysql_connection(connection) {

}

db_opr_base::~db_opr_base() {

}

bool db_opr_base::query(SQL_OPERATE_TYPES opr) {
    std::string statment;
    if (opr == SQL_OPR_SELECT) {
        build_select_statment(statment);
        if (!m_mysql_connection->query(statment)) {
            return false;
        }
        return read_from_res();
    } else if (opr == SQL_OPR_INSERT) {
        build_insert_statment(statment);
        return m_mysql_connection->insert(statment) > 0;
    } else if (opr == SQL_OPR_UPDATE) {
        build_update_statment(statment);
        return m_mysql_connection->modify(statment) > 0;
    } else if (opr == SQL_OPR_DELETE) {
        build_delete_statment(statment);
        return m_mysql_connection->modify(statment) > 0;
    } else if (opr == SQL_OPR_INSERT_OR_UPDATE) {
        build_insert_or_update_statment(statment);
        return m_mysql_connection->modify(statment) > 0;
    } 
    return false;
};
