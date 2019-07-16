#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

#include <unordered_map>
#include "network.h"

USING_XLOGIC

class session_manager {
private:
    session_manager();
    ~session_manager();

public:
    static session_manager *get_instance();
    static void destroy();

    void set_session(uint32_t session_id, uint64_t player_id);

private:
    static session_manager *m_instance;
    std::unordered_map<uint32_t, connector *>   m_session2connector;          // session对应的连接，可能有多个conn server
    std::unordered_map<uint32_t, uint64_t>      m_session2player;             // session对应的玩家
};

#endif //__SESSION_MANAGER_H__
