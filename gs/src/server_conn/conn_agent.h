#ifndef __CONN_AGENT_H__
#define __CONN_AGENT_H__

#include "agent.h"

USING_XLOGIC

class conn_agent : public agent {
public:
    conn_agent();
    ~conn_agent()

public:
    void set_player_id(uint64_t);
    void set_user_id(uint64_t);
    void set_session_id(uint32_t);
    uint64_t get_player_id();
    uint64_t get_user_id();
    uint32_t get_session_id();

private:
    uint64_t player_id;
    uint64_t user_id;
    uint32_t session_id;
};

#endif //__CONN_AGENT_H__
