#include "agent_manager.h"
#include "client_agent.h"

agent_manager::agent_manager() {

}
agent_manager::~agent_manager() {

}

agent_manager *agent_manager::m_instance = nullptr;
agent_manager *agent_manager::get_instance() {
    if (m_instance == nullptr) {
        m_instance = new agent_manager();
    }
    return m_instance;
}

void agent_manager::destroy() {
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

agent *agent_manager::new_agent(struct bufferevent *bev) {
    uint32_t session_id = ++m_session_generator;
    client_agent * ag = new client_agent(bev);
    ag->set_session_id(session_id);
    m_agents.insert(std::make_pair(session_id, ag));
    return ag;
}

void agent_manager::delete_agent(agent *ag) {
    for (auto &it : m_agents) {
        if (it.second == ag) {
            delete ag;
            m_agents.erase(it.first);
            break;
        }
    }
}

agent *agent_manager::get_agent_by_session_id(uint32_t session_id) {
    auto it = m_agents.find(session_id);
    if (it != m_agents.end()) {
        return it->second;
    }
    return nullptr;
}

void agent_manager::auth_agent_by_session_id(uint32_t session_id, uint64_t user_id, uint64_t player_id) {
    agent * ag = get_agent_by_session_id(session_id);
    if (ag == nullptr) {
        return;
    }
    // 只存client_agent对象，所以强传没问题，就为了提供一点点效率，为了安全可以使用dynamic_cast
    client_agent *cli_ag = (client_agent*)ag;
    if (user_id != 0) {
        cli_ag->set_user_id(user_id);
    }
    if (player_id != 0) {
        cli_ag->set_player_id(player_id);
    }
    cli_ag->auth(true);
}
