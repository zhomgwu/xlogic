#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <string>
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "type_def.h"
#include "noncopyable.h"

XLOGIC_BEGIN

class connector;
class connector_handler {
public:
	virtual void on_connect_success(connector *conn) = 0;
	virtual void on_connect_fail(connector *conn) = 0;
	virtual void on_disconnect(connector *conn) = 0;
	virtual void on_message(connector *conn, void * data, uint32_t length) = 0;
};

class message_processor;
class connector : public noncopyable {
public:
	connector();
	virtual ~connector();

public:

	virtual bool init(struct event_base * base, std::string host, uint16_t port, connector_handler * handler);
	virtual bool connect(uint32_t timeout = 0);
	virtual void close();
	virtual bool send(void *data, uint32_t length);
	virtual void do_recv();

	bool is_connecting();
	connector_handler * get_handler();

private:

	static void conn_readcb(struct bufferevent *bev, void *user_data);
	static void conn_writecb(struct bufferevent *bev, void *user_data);
	static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);

private:

	char *                  				m_buffer_read;
	uint16_t 								m_port;	
	bool 									m_is_connecting;
	connector_handler * 					m_conn_handler;
	struct event_base *						m_event_base;
	struct bufferevent * 					m_bufferevent;
	message_processor *        				m_msg_proc;
	std::string 							m_host;
};

XLOGIC_END

#endif //__CONNECTOR_H__
