#include "login_handler.h"

bool login_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void login_handler::on_new_agent(agent* ag) {

}

void login_handler::on_disconnect(agent* ag) {

}

void login_handler::on_message(agent* ag, void *data, int len) {
    // 来自登录服的信息，一般情况下直接发送给客户端

}
