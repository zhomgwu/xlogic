#include "game_handler.h"

bool game_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void game_handler::on_new_agent(agent* ag) {

}

void game_handler::on_disconnect(agent* ag) {

}

void game_handler::on_message(agent* ag, void *data, int len) {
    // 来自游戏服务的信息，一般情况下直接发送给客户端

}
