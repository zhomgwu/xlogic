#include "login_handler.h"
#include "logger_manager.h"

agent * login_handler::m_login_agent = nullptr;
bool login_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void login_handler::on_new_agent(agent* ag) {
    if (m_login_agent) {
        LOGERROR("game agent has been existed!");
        return;
    }
    m_login_agent = ag;
}

void login_handler::on_disconnect(agent* ag) {
    m_login_agent = nullptr;
    LOGWARN("login agent was disconnected!");
}

void login_handler::on_message(agent* ag, void *data, int len) {
    // 来自登录服的信息，一般情况下直接发送给客户端
    inner_handler::on_message(ag, data, len);
}
