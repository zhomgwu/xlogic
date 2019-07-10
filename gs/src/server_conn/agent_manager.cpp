#include "agent_manager.h"

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
    agent * ag = new agent(bev);
    uint32_t session_id = ++m_session_generator;
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
