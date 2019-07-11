#include "client_agent.h"

client_agent::client_agent(struct bufferevent *bev) 
: agent(bev)
, m_is_auth(false)
, m_player_id(0)
, m_user_id(0)
, m_session_id(0) {

}

client_agent::~client_agent() {

}

void client_agent::auth(bool is_auth) {
    m_is_auth = is_auth;
}

void client_agent::set_player_id(uint64_t player_id) {
    m_player_id = player_id;
}

void client_agent::set_user_id(uint64_t user_id) {
    m_user_id = user_id;
}

void client_agent::set_session_id(uint32_t session_id) {
    m_session_id = session_id;
}

bool client_agent::is_auth() {
    return m_is_auth;
}

uint64_t client_agent::get_player_id() {
    return m_player_id;
}

uint64_t client_agent::get_user_id() {
    return m_user_id;
}

uint32_t client_agent::get_session_id() {
    return m_session_id;
}
