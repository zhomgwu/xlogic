#ifndef __INNER_LISTENER_H__
#define __INNER_LISTENER_H__

#include "listener.h"

XLOGIC_BEGIN

enum SERVER_TYPE {
    SERVER_TYPE_NULL = 0,
    SERVER_TYPE_CONN,
    SERVER_TYPE_GAME,
    SERVER_TYPE_BATTLE,
    SERVER_TYPE_DATABASE,
};

// 内部监听器，主要用于服务器之间的监听，只接受一个连接
class inner_listener : public listener, public listener_handler {
public:
    inner_listener();
    ~inner_listener();

public:
    void set_peer_srv_type(uint32_t srv_type);
    void set_authorize_host(std::string host);
    bool send(void *data, int len);

    virtual bool check_address(struct sockaddr *sa, int socklen);
    virtual void on_new_agent(agent* ag);
    virtual void on_disconnect(agent* ag);

private:
    uint32_t    m_peer_srv_type;            // 对端服务器
    agent*      m_peer_srv_agent;           // 对端代理对象，用于收发
    std::string m_authorize_host;           // 授权ip地址，如果设置则只允许对应的ip，否则不限制
};

XLOGIC_END

#endif //__INNER_LISTENER_H__
