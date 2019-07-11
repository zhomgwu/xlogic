#ifndef __AGENT_MANAGER_H__
#define __AGENT_MANAGER_H__

#include "network.h"
#include <map>

USING_XLOGIC

class agent_manager : public agent_maker {
private:
    agent_manager();
    virtual ~agent_manager();

public:
    static agent_manager *get_instance();
    static void destroy();

    virtual agent *new_agent(struct bufferevent *bev);
    virtual void delete_agent(agent *ag);

    agent *get_agent_by_session_id(uint32_t session_id);
    void auth_agent_by_session_id(uint32_t session_id, uint64_t user_id, uint64_t player_id);

private:
    static agent_manager *          m_instance;
    uint32_t                        m_session_generator;
    std::map<uint32_t, agent *>     m_agents;
    std::map<uint64_t, uint32_t>    m_user2session;
    std::map<uint64_t, uint32_t>    m_player2session;
};

#endif //__AGENT_MANAGER_H__
