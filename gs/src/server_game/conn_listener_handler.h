#ifndef __CONN_LISTENER_HANDLER_H__
#define __CONN_LISTENER_HANDLER_H__

#include "network.h"

USING_XLOGIC

class conn_listener_handler : public listener_handler {
public:
    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(agent* ag);
    virtual void on_disconnect(agent* ag);
    virtual void on_message(agent* ag, void *data, int len);

    static agent *m_conn_agent;
};

#endif //__CONN_LISTENER_HANDLER_H__
