
#ifndef __GAME_CONNECTOR_HANDLER_H__
#define __GAME_CONNECTOR_HANDLER_H__

#include "inner_handler.h"

USING_XLOGIC

class game_connector_handler : public inner_handler {
public:
    virtual void on_connect_success(connector *conn) override;
    virtual void on_connect_fail(connector *conn) override;
    virtual void on_disconnect(connector *conn) override;
    virtual void on_message(connector *conn, void * data, uint32_t length) override;

    static connector * m_game_connector;
};

#endif //__GAME_CONNECTOR_HANDLER_H__
