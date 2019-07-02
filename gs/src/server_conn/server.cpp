#include "server.h"
#include "poller.h"

USING_XLOGIC

server::server () {

}

server::~server() {

}

bool server::server_init(std::string conf_path) {
    // 读取服务器配置文件

    // 初始化网络模块

    // 初始化数据库模块

    // 初始化游戏配置文件

    // 初始化游戏模块
    return true;
}

void server::server_run() {
    // network update

    // message dispatch

    // game logic update

}

void server::server_exit() {

}

bool server::init_log() {
    return true;
}

bool server::init_network() {
    return true;
}

bool server::init_configurate() {
    return true;
}

bool server::init_db() {
    return true;
}

bool server::init_game() {
    return true;   
}

poller *server::get_poller() {
    return m_poller;
}


