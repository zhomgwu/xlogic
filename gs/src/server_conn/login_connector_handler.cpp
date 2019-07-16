#include "login_connector_handler.h"
#include "logger_manager.h"
#include "inner_handler.h"

connector * login_connector_handler::m_login_connector = nullptr;
void login_connector_handler::on_connect_success(connector *conn) {
    if (m_login_connector) {
        LOGERROR("login connector has been existed! host=%s, port=%d", 
            m_login_connector->get_host().c_str(), m_login_connector->get_port());
        return;
    }
    m_login_connector = conn;
}

void login_connector_handler::on_connect_fail(connector *conn) {
    LOGERROR("login connector connect fail! host=%s, port=%d", conn->get_host().c_str(), conn->get_port());
}

void login_connector_handler::on_disconnect(connector *conn) {
    m_login_connector = nullptr;
    LOGERROR("login connector disconnect! host=%s, port=%d", conn->get_host().c_str(), conn->get_port());
}

void login_connector_handler::on_message(connector *conn, void *data, uint32_t len) {
    inner_handler::on_message(conn, data, len);
}
