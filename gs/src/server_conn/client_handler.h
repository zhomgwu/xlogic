#ifndef __CLIENT_HANDLER_H_
#define __CLIENT_HANDLER_H_

#include "network.h"

USING_XLOGIC

class client_handler : public listener_handler {
public:
    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(agent* ag);
    virtual void on_disconnect(agent* ag);
    virtual void on_message(agent* ag, void *data, int len);
};

#endif //__CLIENT_HANDLER_H_