#ifndef __CONN_AGENT_H__
#define __CONN_AGENT_H__

#include "agent.h"

USING_XLOGIC

class client_agent : public agent {
public:
    client_agent(struct bufferevent *);
    virtual ~client_agent();

public:
    void auth(bool is_auth);
    void set_player_id(uint64_t player_id);
    void set_user_id(uint64_t user_id);
    void set_session_id(uint32_t session_id);
    bool is_auth();
    uint64_t get_player_id();
    uint64_t get_user_id();
    uint32_t get_session_id();

private:
    bool m_is_auth;
    uint64_t m_player_id;
    uint64_t m_user_id;
    uint32_t m_session_id;
};

#endif //__CONN_AGENT_H__
