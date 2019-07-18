#include "handle_register.h"
#include "logger_manager.h"
#include "server_message.h"

static void subcribe_conn_cmd(uint32_t cmd) {
    
}

handle_register::handle_register() {
}

handle_register::~handle_register() {

}

handle_register *handle_register::m_instance = nullptr;
handle_register *handle_register::get_instance() {
    if (m_instance == nullptr) {
        m_instance = new handle_register();
    }
    return m_instance;
}

void handle_register::destroy() {
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void handle_register::add_player_handle(uint32_t cmd, player_handler_func func) {
    if (m_player_handler.find(cmd) != m_player_handler.end()) {
        LOGERROR("repeated register cmd=%d", cmd);
        return;
    }
    m_player_handler[cmd] = func;
}

void handle_register::add_handle(uint32_t cmd, handler_func func) {
    if (m_handler.find(cmd) != m_handler.end()) {
        LOGERROR("repeated register cmd=%d", cmd);
        return;
    }
    m_handler[cmd] = func;
}

void handle_register::dispatch(void *data, int len) {
    inner_message_head *head = (inner_message_head *)data;
    switch (head->message_id) {
        // 新连接
        case INNER_SOCK_NEW: {

            break;
        }
        // 连接关闭
        case INNER_SOCK_CLOSE: {

            break;
        }
        // 客户端消息
        case INNER_MSG_FORWARD: {
            break;
        }
        // 服务器关闭
        case INNER_SERVER_CLOSE: {
            break;
        }
        // 其他不应该来到的信息号
        default: {

            break;
        }
    }
}

