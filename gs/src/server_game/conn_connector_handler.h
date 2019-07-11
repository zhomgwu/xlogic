#ifndef __CONN_CONNECTOR_HANDLER_H__
#define __CONN_CONNECTOR_HANDLER_H__

#include "connector.h"

USING_XLOGIC

class conn_connector_handler : public connector_handler{
public:
    virtual void on_connect_success(connector *conn) override;
    virtual void on_connect_fail(connector *conn) override;
    virtual void on_disconnect(connector *conn) override;
    virtual void on_message(connector *conn, void * data, uint32_t length) override;
};

#endif //__CONN_CONNECTOR_HANDLER_H__
