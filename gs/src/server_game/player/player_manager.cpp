#include "player_manager.h"

player_manager::player_manager() {

    
}

player_manager::~player_manager() {

}

player_manager* player_manager::m_instance = nullptr;
player_manager * player_manager::get_instance() {
    if (m_instance == nullptr) {
        m_instance = new player_manager();
    }
    return m_instance;
}

void player_manager::destroy() {
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void player_manager::on_login(uint64_t player_id) {

}

void player_manager::on_logout(uint64_t player_id) {

}

player *player_manager::get_player(uint64_t player_id) {
    if (m_players.find(player_id) != m_players.end()) {
        return m_players[player_id];
    }
    return nullptr;
}

player* player_manager::new_player() {
    return nullptr;
}

void player_manager::save_player(uint64_t player_id) {

}

void player_manager::save_player(player * pr) {

}

