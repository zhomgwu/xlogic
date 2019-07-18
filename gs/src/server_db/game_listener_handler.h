#ifndef __GAME_LISTENER_HANDLER_H__
#define __GAME_LISTENER_HANDLER_H__

#include "network.h"

USING_XLOGIC

class game_listener_handler : public listener_handler {
public:
    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(agent* ag);
    virtual void on_disconnect(agent* ag);
    virtual void on_message(agent* ag, void *data, int len);

    static agent *m_game_agent;
};

#endif //__GAME_LISTENER_HANDLER_H__
