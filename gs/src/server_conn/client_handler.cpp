#include "client_handler.h"

bool client_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void client_handler::on_new_agent(agent* ag) {

}

void client_handler::on_disconnect(agent* ag) {

}

void client_handler::on_message(agent* ag, void *data, int len) {
    // 来自客户端的消息，解析，根据id分配到订阅的服务器去
    


}
