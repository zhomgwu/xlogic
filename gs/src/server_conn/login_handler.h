#ifndef __LOGIN_HANDLER_H__
#define __LOGIN_HANDLER_H__

#include "listener.h"

USING_XLOGIC

class login_handler : public listener_handler {
public:
    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(agent* ag);
    virtual void on_disconnect(agent* ag);
    virtual void on_message(agent* ag, void *data, int len);
};

#endif //__LOGIN_HANDLER_H__
