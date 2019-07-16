#ifndef __INNER_HANDLER_H__
#define __INNER_HANDLER_H__

#include "network.h"

USING_XLOGIC

class inner_handler : public connector_handler {
public:
    virtual void on_connect_success(connector *conn) override;
    virtual void on_connect_fail(connector *conn) override;
    virtual void on_disconnect(connector *conn) override;
    virtual void on_message(connector *conn, void * data, uint32_t length) override;
};

#endif //__INNER_HANDLER_H__
