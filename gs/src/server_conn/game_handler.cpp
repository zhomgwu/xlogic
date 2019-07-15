#include "game_handler.h"
#include "server_message.h"
#include "logger_manager.h"
#include "agent_manager.h"

agent * game_handler::m_game_agent = nullptr;
bool game_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void game_handler::on_new_agent(agent* ag) {
    if (m_game_agent) {
        LOGERROR("game agent has been existed!");
        return;
    }
    m_game_agent = ag;
}

void game_handler::on_disconnect(agent* ag) {
    m_game_agent = nullptr;
    LOGWARN("game agent was disconnected!");
}

void game_handler::on_message(agent* ag, void *data, int len) {
    inner_handler::on_message(ag, data, len);
}
