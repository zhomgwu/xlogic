#ifndef __GAME_LOOPER_H__
#define __GAME_LOOPER_H__

#include "app_looper.h"
#include "network.h"
#include <unordered_map>

class game_looper : public app_looper, public xlogic::listener_handler {
public:
    virtual ~game_looper();

public:
    virtual void on_start();
    virtual void on_end();
    virtual void on_loading_begin();
    virtual void on_loading_end();
    virtual void on_update();
    virtual void on_sec(uint64_t ts);

    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(xlogic::agent* ag);
    virtual void on_disconnect(xlogic::agent* ag);

private:
    uint32_t session_id;
    std::unordered_map<uint32_t, xlogic::agent *> m_agents;
};

#endif //__GAME_LOOPER_H__
