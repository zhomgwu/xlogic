#include "conn_listener_handler.h"
#include "logger_manager.h"

bool conn_listener_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

agent *conn_listener_handler::m_conn_agent = nullptr;
void conn_listener_handler::on_new_agent(agent* ag) {
    if (m_conn_agent) {
        LOGERROR("conn agent has been existed!");
        return;
    }
    m_conn_agent = ag;
}

void conn_listener_handler::on_disconnect(agent* ag) {
    m_conn_agent = nullptr; 
    LOGERROR("conn agent has disconnected!");
}

void conn_listener_handler::on_message(agent* ag, void *data, int len) {
    
}
