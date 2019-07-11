#include "game_handler.h"
#include "server_message.h"
#include "logger_manager.h"
#include "agent_manager.h"

extern agent * g_game_agent;

bool game_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void game_handler::on_new_agent(agent* ag) {
    if (g_game_agent) {
        LOGERROR("game agent has been existed!");
        return;
    }
    g_game_agent = ag;
}

void game_handler::on_disconnect(agent* ag) {
    g_game_agent = nullptr;
    LOGWARN("game agent was disconnected!");
}

void game_handler::on_message(agent* ag, void *data, int len) {
    // 来自游戏服务的信息，一般情况下直接发送给客户端
    inner_message_head * head = (inner_message_head *)data;
    
    switch(head->message_id) {
        case INNER_MSG_FORWARD: {
            message_forward * forward = (message_forward*)data;
            agent_manager::get_instance()->get_agent_by_session_id(forward->session_id);
            break;
        }
        case INNER_MSG_BROADCAST: {
            
            break;
        }
        case INNER_MSG_SUBSCRIBE: {
            
            break;
        }
    }


}
