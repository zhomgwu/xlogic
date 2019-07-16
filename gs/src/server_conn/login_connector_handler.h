#ifndef __LOGIN_CONNECTOR_HANDLER_H__
#define __LOGIN_CONNECTOR_HANDLER_H__

#include "inner_handler.h"

class login_connector_handler : public inner_handler {
public:
    virtual void on_connect_success(connector *conn) override;
    virtual void on_connect_fail(connector *conn) override;
    virtual void on_disconnect(connector *conn) override;
    virtual void on_message(connector *conn, void * data, uint32_t length) override;

    static connector * m_login_connector;
};

#endif //__LOGIN_CONNECTOR_HANDLER_H__
