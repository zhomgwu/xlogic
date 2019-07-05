#include "server.h"
#include "yaml-cpp/yaml.h"
#include "logger_manager.h"

USING_XLOGIC

server::server ()
: m_poller(nullptr) {

}

server::~server() {

}

bool server::server_init(std::string conf_path) {
    m_status = SS_OPENING;
    // 读取服务器配置文件
    if (!init_server_config(conf_path)) return false;
    // 初始化网络模块
    if (!init_network()) return false;
    // 初始化数据库模块
    if (!init_db()) return false;
    // 初始化游戏配置文件
    if (!init_configurate()) return false;
    // 初始化游戏模块
    if (!init_game()) return false;

    m_status = SS_OPEN;
    return true;
}

void server::server_run() {
    // network update
    while (m_status != SS_CLOSE) {
        // 正在关闭
        if (m_status == SS_WILL_CLOSE) {
            m_status = SS_CLOSING;
            m_poller->stop();
            m_game_looper->on_end();
            m_status = SS_CLOSE;
        } else {
            // message dispatch
            
            // game logic update
            m_game_looper->on_update();
        }
    }
}

void server::server_exit() {

}

void server::on_signal(int signo) {
    if (signo == SIGINT) {
        m_status = SS_CLOSING;
    } else if (signo == SIGTERM) {
        m_status = SS_CLOSE;
    }
}

bool server::init_server_config(std::string path) {
    // 默认配置
    m_config.client_listener_port = 6001;
    m_config.game_listener_port = 6002;
    m_config.login_listener_port = 6003;
    m_config.max_client = 6004;

    YAML::Node yaml_node;
    try {
        yaml_node = YAML::LoadFile(path);
    }
    catch (std::runtime_error e) {
        LOGERROR("open yaml file error, path=%s", path.c_str());
        return false;
    }
    
    if (yaml_node["server_conn"].IsDefined()) {
        YAML::Node node = yaml_node["server_conn"];
        if (node["client_listener"].IsDefined()) {
            m_config.client_listener_port = node["client_listener"].as<uint16_t>();
        }
        if (node["_game_listener"].IsDefined()) {
            m_config.game_listener_port = node["_game_listener"].as<uint16_t>();
        }
        if (node["_login_listener"].IsDefined()) {
            m_config.login_listener_port = node["_login_listener"].as<uint16_t>();
        }
        if (node["max_client"].IsDefined()) {
            m_config.max_client = node["max_client"].as<uint16_t>();
        }
    }
    return true;
}

bool server::init_network() {
    m_poller = new poller();
    if (!m_poller->init()) {
        SAFE_DELETE(m_poller);
        return false;
    }

    m_client_listener = new listener();
    if (!m_client_listener->init(m_poller->get_event_base(), m_config.client_listener_port, )) {
        return false;
    }

    return true;
}

bool server::init_db() {
    return true;
}

bool server::init_configurate() {
    return true;
}

bool server::init_game() {
    return true;   
}

poller *server::get_poller() {
    return m_poller;
}


