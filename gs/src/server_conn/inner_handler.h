#ifndef __INNER_HANDLER_H__
#define __INNER_HANDLER_H__

#include "inner_handler.h"

USING_XLOGIC

class inner_handler : public listener_handler {
public:
    virtual bool check_address(struct sockaddr *sa, int socklen) override;
    virtual void on_new_agent(agent* ag) override;
    virtual void on_disconnect(agent* ag) override;
    virtual void on_message(agent* ag, void *data, int len) override;
};

#endif //__INNER_HANDLER_H__
