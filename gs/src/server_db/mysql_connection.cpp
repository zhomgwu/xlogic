#include "mysql_connection.h"
#include "logger_manager.h"

mysql_connection::mysql_connection()
: m_mysql(nullptr)
, m_mysql_res(nullptr) {

}

mysql_connection::~mysql_connection() {

}

bool mysql_connection::connect(const std::string& host, unsigned int port, 
        const std::string& user, const std::string& password, const std::string& db) {
    if (m_mysql != nullptr) {
        LOGERROR("mysql has connected, you must close it first!");
        return false;
    }

    m_mysql = mysql_init(nullptr);
    do {
        int connect_timeout = 10;
        int write_timeout = 5;
        int read_timeout = 5;
        int is_reconnct = 1;
        if (mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "utf8")!= 0) break;
        if (mysql_options(m_mysql, MYSQL_OPT_CONNECT_TIMEOUT, &connect_timeout)!= 0) break;
        if (mysql_options(m_mysql, MYSQL_OPT_WRITE_TIMEOUT, &write_timeout)!= 0) break;
        if (mysql_options(m_mysql, MYSQL_OPT_READ_TIMEOUT, &read_timeout)!= 0) break;
        if (mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &is_reconnct)!= 0) break;

        if (mysql_real_connect(m_mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 
            port, nullptr, CLIENT_REMEMBER_OPTIONS) == nullptr) {
            break;
        }
        LOGDEBUG("connect to mysql success, host=%s, port=%d", host.c_str(), port);
        return true;
    }while(false);

    const char * error_str = mysql_error(m_mysql);
    LOGERROR("error_str=%s", error_str);
    mysql_close(m_mysql);
    return false;
}

bool mysql_connection::close() {
    if (m_mysql) {
        mysql_close(m_mysql);
        m_mysql = nullptr;
    }
    return true;
}

bool mysql_connection::query(const std::string &statement) {
    if (m_mysql == nullptr || statement.size() == 0) {
        return false;
    }
    clear_res();
    int ret = mysql_real_query(m_mysql, statement.c_str(), statement.size());
    if (ret != 0) {
        int error_no = mysql_errno(m_mysql);
        const char * error_str = mysql_error(m_mysql);
        LOGERROR("error_no=%d, error_msg=%s",error_no, error_str);
        return false;
    }
    m_mysql_res = mysql_store_result(m_mysql);
    return true;
}

int mysql_connection::insert(const std::string &statement) {
    if (m_mysql == nullptr || statement.size() == 0) {
        return 0;
    }
    clear_res();
    int ret = mysql_real_query(m_mysql, statement.c_str(), statement.size());
    if (ret != 0) {
        int error_no = mysql_errno(m_mysql);
        const char * error_str = mysql_error(m_mysql);
        LOGERROR("error_no=%d, error_msg=%s",error_no, error_str);
        return 0;
    }
    return mysql_insert_id(m_mysql);
}

int mysql_connection::modify(const std::string &statement) {
    if (m_mysql == nullptr || statement.size() == 0) {
        return 0;
    }
    clear_res();
    int ret = mysql_real_query(m_mysql, statement.c_str(), statement.size());
    if (ret != 0) {
        int error_no = mysql_errno(m_mysql);
        const char * error_str = mysql_error(m_mysql);
        LOGERROR("error_no=%d, error_msg=%s",error_no, error_str);
        return 0;
    }
    return mysql_affected_rows(m_mysql);
}

bool mysql_connection::clear_res() {
    if (m_mysql_res) {
        while (mysql_next_result(m_mysql) == 0) {
            continue;
        }
        mysql_free_result(m_mysql_res);
        m_mysql_res = nullptr;
    }
    return true;
}

bool mysql_connection::escape_string(char* dst, const char* src, int len) {
    return mysql_real_escape_string(m_mysql, dst, src, len);
}

int mysql_connection::num_rows() {
    if (m_mysql_res) {
        return mysql_num_rows(m_mysql_res);    
    }
    return 0;
}

int mysql_connection::num_fields() {
    if (m_mysql_res){
        return mysql_num_fields(m_mysql_res);
    }
    return 0;
}

MYSQL_ROW mysql_connection::fetch_row() {
    if (m_mysql_res) {
        return mysql_fetch_row(m_mysql_res);
    }
    return nullptr;
}

unsigned long* mysql_connection::fetch_lengths() {
    if (m_mysql_res) {
        return mysql_fetch_lengths(m_mysql_res);
    }
    return nullptr;
}

