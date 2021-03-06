#include "server.h"
#include <chrono>
#include <thread>
#include "yaml-cpp/yaml.h"
#include "logger_manager.h"
#include "client_handler.h"
#include "login_connector_handler.h"
#include "game_connector_handler.h"
#include "agent_manager.h"

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
    // 游戏开始
    m_app_looper->on_start();
    // network update
    while (m_status != SS_CLOSE) {
        // 正在关闭
        if (m_status == SS_WILL_CLOSE) {
            m_status = SS_CLOSING;
            m_poller->stop();
            m_app_looper->on_end();
            m_status = SS_CLOSE;
        } else {
            // 使用一定的帧数来跑，服务器每秒20帧
            auto begin_time = std::chrono::high_resolution_clock::now();
            {
                // message dispatch
                m_poller->step();
                // game logic update
                m_app_looper->on_update();
            }
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::milliseconds cost_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
            std::chrono::milliseconds wait_time = std::chrono::milliseconds(50) - cost_time;
            if (wait_time.count() > 0) {
                std::this_thread::sleep_for(wait_time);
                // usleep(wait_time.count() * 1000);
            }
        }
    }
    // 游戏结束
    m_app_looper->on_end();
}

void server::server_exit() {
    SAFE_DELETE(m_poller);
    SAFE_DELETE(m_app_looper);
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
    m_config.game_host = "127.0.0.1";
    m_config.game_port = 6101;
    m_config.login_host = "127.0.0.1";
    m_config.login_port = 6201;
    m_config.max_client = 6004;

    YAML::Node yaml_node;
    try {
        yaml_node = YAML::LoadFile(path);
    }
    catch (std::runtime_error e) {
        LOGERROR("open yaml file error, path=%s", path.c_str());
        return false;
    }
    // 本地监听，监听玩家连接
    if (yaml_node["server_conn"].IsDefined()) {
        YAML::Node node = yaml_node["server_conn"];
        if (node["client_listener"].IsDefined()) {
            m_config.client_listener_port = node["client_listener"].as<uint16_t>();
        }
        if (node["max_client"].IsDefined()) {
            m_config.max_client = node["max_client"].as<uint16_t>();
        }
    }
    // 游戏服务器
    if (yaml_node["server_game"].IsDefined()) {
        YAML::Node node = yaml_node["server_game"];
        if (node["listener"].IsDefined()) {
            m_config.game_port = node["listener"].as<uint16_t>();
        }
    }
    // 登录服务器
    if (yaml_node["server_login"].IsDefined()) {
        YAML::Node node = yaml_node["server_login"];
        if (node["listener"].IsDefined()) {
            m_config.game_port = node["listener"].as<uint16_t>();
        }
    }

    return true;
}

bool server::init_network() {
    if (m_poller) {
        LOGERROR("network poller initialized already");
        return false;
    }
    m_poller = new poller();
    if (!m_poller->init()) {
        SAFE_DELETE(m_poller);
        return false;
    }

    // 客户端监听
    m_client_listener = new listener();
    m_client_listener->set_agent_maker(agent_manager::get_instance());
    if (!m_client_listener->init(m_poller->get_event_base(), m_config.client_listener_port, new client_handler())
        || !m_client_listener->listen()) {
        return false;
    }
    // game服务器监听
    m_game_connector = new connector();
    if (!m_game_connector->init(m_poller->get_event_base(), m_config.game_host, m_config.game_port, new game_connector_handler())
        || !m_game_connector->connect()) {
        return false;
    }
    // login服务器监听
    m_login_connector = new connector();
    if (!m_login_connector->init(m_poller->get_event_base(), m_config.login_host, m_config.login_port, new login_connector_handler())
        || !m_login_connector->connect()) {
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
    if (m_app_looper) {
        LOGERROR("app looper initialized already");
        return false;
    }
    m_app_looper = new game_looper();
    return true;   
}

server_config *server::get_server_config() {
    return &m_config;
}

poller *server::get_poller() {
    return m_poller;
}
