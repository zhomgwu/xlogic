#include "inner_handler.h"
#include "message_subscription.h"
#include "server_message.h"
#include "agent_manager.h"

void inner_handler::on_connect_success(connector *conn) {
}

void inner_handler::on_connect_fail(connector *conn) {
}

void inner_handler::on_disconnect(connector *conn) {
}

void inner_handler::on_message(connector *conn, void *data, uint32_t len) {
    // 来自游戏服务的信息，一般情况下直接发送给客户端
    inner_message_head * head = (inner_message_head *)data;
    
    switch(head->message_id) {
        // 转发
        case INNER_MSG_FORWARD: {
            void *real_data = nullptr;
            uint32_t real_len = 0;
            uint32_t session_id;

            parse_message_forward(data, len, session_id, &real_data, real_len);
            agent_manager::get_instance()->send_by_session(session_id, real_data, real_len);
            break;
        }
        // 广播
        case INNER_MSG_BROADCAST: {
            void *real_data = nullptr;
            uint32_t real_len = 0;
            std::vector<uint32_t> sessions;

            parse_message_broadcast(data, len, sessions, &real_data, real_len);
            for (auto & session_id : sessions) {
                agent_manager::get_instance()->send_by_session(session_id, real_data, real_len);
            }
            break;
        }
        // 消息订阅
        case INNER_MSG_SUBSCRIBE: {
            message_subscribe * msg = (message_subscribe*)data;
            message_subscription::get_instance()->subscribe(msg->subscribe_id, conn);
            break;
        }
        default: {
            break;
        }
    }
}

