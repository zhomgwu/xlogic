#include "game_listener_handler.h"
#include "logger_manager.h"

bool game_listener_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

agent *game_listener_handler::m_game_agent = nullptr;
void game_listener_handler::on_new_agent(agent* ag) {
    if (m_game_agent) {
        LOGERROR("conn agent has been existed!");
        return;
    }
    m_game_agent = ag;
}

void game_listener_handler::on_disconnect(agent* ag) {
    m_game_agent = nullptr; 
    LOGERROR("conn agent has disconnected!");
}

void game_listener_handler::on_message(agent* ag, void *data, int len) {
    
}
