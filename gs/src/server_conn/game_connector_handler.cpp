#include "game_connector_handler.h"
#include "logger_manager.h"

connector * game_connector_handler::m_game_connector = nullptr;
void game_connector_handler::on_connect_success(connector *conn) {
    if (m_game_connector) {
        LOGERROR("game connector has been existed! host=%s, port=%d", 
            m_game_connector->get_host().c_str(), m_game_connector->get_port());
        return;
    }
    m_game_connector = conn;
}

void game_connector_handler::on_connect_fail(connector *conn) {
    LOGERROR("game connector connect fail! host=%s, port=%d", conn->get_host().c_str(), conn->get_port());
}

void game_connector_handler::on_disconnect(connector *conn) {
    m_game_connector = nullptr;
    LOGERROR("game connector disconnect! host=%s, port=%d", conn->get_host().c_str(), conn->get_port());
}

void game_connector_handler::on_message(connector *conn, void *data, uint32_t len) {
    inner_handler::on_message(conn, data, len);
}
