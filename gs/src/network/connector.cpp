#include "connector.h"

#define RECV_BUFFER_SIZE 4096

connector::connector()
: m_buffer_read(nullptr)
, m_port(0)
, m_conn_handler(nullptr)
, m_event_base(nullptr)
, m_socket_msg(nullptr)
, m_bufferevent(nullptr) {
    m_buffer_read = (char*)malloc(RECV_BUFFER_SIZE);
    m_socket_msg = new socket_message();
}

connector::~connector() {
    if (m_socket_msg) {
        delete m_socket_msg;
        m_socket_msg = nullptr;
    }
}

bool connector::init(struct event_base * base, std::string host, uint32_t port, connector_handler * handler) {
    if (!base) {
        return false;
    }
    if (m_port <= 1024 || m_port >= 65535) {
        return false;
    }
    m_host = host;
    m_event_base = base;
    m_conn_handler = handler;
    return true;
}

bool connector::connect(uint32_t timeout) {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_host);

    if (inet_pton(AF_INET, m_host.c_str(), &sin.sin_addr) < 0) {
        return false;
    }

    m_bufferevent = bufferevent_socket_new(m_event_base, -1, BEV_OPT_CLOSE_ON_FREE);
    if (!m_bufferevent) {
        return false;
    }

    if (bufferevent_socket_connect(m_bufferevent, (struct sockaddr *)&sin, sizeof(sin))!= 0) {
        bufferevent_free(m_bufferevent);
        return false;
    }

    bufferevent_setcb(m_bufferevent, connector::conn_readcb, connector::conn_writecb, connector::conn_eventcb, (void*)this)
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    return true;
}

void connector::close() {
    if (m_bufferevent) {
        bufferevent_free(m_bufferevent);
        m_bufferevent = nullptr;
    }
}

void connector::send(void *data, uint32_t length) {
    if (0 != bufferevent_write(m_bufferevent, data, length)) {
        return false;
    }
    return true;
}

void connector::do_recv() {
    if (m_bufferevent) {
        size_t recv_length = 0;
        recv_length = bufferevent_read(m_bufferevent, m_buffer_read, RECV_BUFFER_SIZE);
        if (recv_length > 0) {
            m_socket_msg->append(m_buffer_read, recv_length);   
        }
    }
}

connector_handler * connector::get_handler() {
    return m_conn_handler;
}

void connector::conn_readcb(struct bufferevent *bev, void *user_data) {
    xlogic::connector* conn = (xlogic::connector*)user_data;
    conn->do_recv();
}

void connector::conn_writecb(struct bufferevent *bev, void *user_data) {

}

void connector::conn_eventcb(struct bufferevent *bev, short events, void *user_data) {
    xlogic::connector* conn = (xlogic::connector*)user_data;
    connector_handler * handler = conn->get_handler();
    if (events & BEV_EVENT_CONNECTED) {
        if (handler) {
            handler->on_connect_success();
        }
    }
    else if (events & BEV_EVENT_ERROR) {
        if (handler) {
            handler->on_connect_fail();
        }
        else {
            handler->on_disconnect();
        }
    }
    else if ( events & BEV_EVENT_EOF) {
        if (handler) {
            handler->on_disconnect();
        }
    }
}