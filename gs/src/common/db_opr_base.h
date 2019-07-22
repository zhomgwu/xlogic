#ifndef __DB_OPR_BASE_H__
#define __DB_OPR_BASE_H__

#include "mysql_connection.h"

enum SQL_OPERATE_TYPES {
    SQL_OPR_UNKNOW = 0,
    SQL_OPR_SELECT,
    SQL_OPR_INSERT,
    SQL_OPR_UPDATE,
    SQL_OPR_DELETE,
    SQL_OPR_INSERT_OR_UPDATE,
};

class db_opr_base {
public:
    db_opr_base(mysql_connection *);
    virtual ~db_opr_base();

    virtual bool query(SQL_OPERATE_TYPES opr);
    virtual bool read_from_res() = 0;
    virtual void build_select_statment(std::string&) = 0;
    virtual void build_insert_statment(std::string&) = 0;
    virtual void build_update_statment(std::string&) = 0;
    virtual void build_delete_statment(std::string&) = 0;
    virtual void build_insert_or_update_statment(std::string&) = 0;

protected:
    mysql_connection *m_mysql_connection;
};

#endif //__DB_OPR_BASE_H__
