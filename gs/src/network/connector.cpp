#include "connector.h"
#include "message_processor.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>
#include <string.h>

#define RECV_BUFFER_SIZE 4096

XLOGIC_BEGIN

connector::connector()
: m_buffer_read(nullptr)
, m_port(0)
, m_is_connecting(false)
, m_conn_handler(nullptr)
, m_event_base(nullptr)
, m_msg_proc(nullptr)
, m_bufferevent(nullptr) {
    m_buffer_read = (char*)malloc(RECV_BUFFER_SIZE);
    m_msg_proc = new message_processor();
}

connector::~connector() {
    if (m_msg_proc) {
        delete m_msg_proc;
        m_msg_proc = nullptr;
    }
}

bool connector::init(struct event_base * base, std::string host, uint16_t port, connector_handler * handler) {
    if (!base) {
        return false;
    }
    if (port <= 1024 || port >= 65535) {
        return false;
    }
    m_host = host;
    m_port = port;
    m_event_base = base;
    m_conn_handler = handler;
    return true;
}

bool connector::connect(uint32_t timeout) {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);

    if (inet_pton(AF_INET, m_host.c_str(), &sin.sin_addr) < 0) {
        return false;
    }

    m_bufferevent = bufferevent_socket_new(m_event_base, -1, BEV_OPT_CLOSE_ON_FREE);
    if (!m_bufferevent) {
        return false;
    }
    
    bufferevent_setcb(m_bufferevent, connector::conn_readcb, connector::conn_writecb, connector::conn_eventcb, (void*)this);
    bufferevent_enable(m_bufferevent, EV_READ | EV_WRITE);
    
    if (bufferevent_socket_connect(m_bufferevent, (struct sockaddr *)&sin, sizeof(sin)) != 0) {
        bufferevent_free(m_bufferevent);
        return false;
    }

    return true;
}

void connector::close() {
    if (m_bufferevent) {
        bufferevent_free(m_bufferevent);
        m_bufferevent = nullptr;
    }
}

bool connector::send(void *data, uint32_t length) {
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
            m_msg_proc->append(m_buffer_read, recv_length); 

            void *entire_data = nullptr;
            int data_len = 0;
            if (m_msg_proc->get_entire_data(&entire_data, data_len)) {
                if (m_conn_handler) {
                    m_conn_handler->on_message(this, entire_data, data_len);
                }
                m_msg_proc->drop_data(data_len);
            }
        }
    }
}

bool connector::is_connecting() {
    return m_is_connecting;
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
            handler->on_connect_success(conn);
        }
    }
    else if (events & BEV_EVENT_ERROR) {
        if (handler) {
            if (conn->is_connecting()) {
                handler->on_connect_fail(conn);
            }
            else {
                handler->on_disconnect(conn);
            }
        }
    }
    else if ( events & BEV_EVENT_EOF) {
        if (handler) {
            handler->on_disconnect(conn);
        }
    }
}

XLOGIC_END
