#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

namespace xlogic {

class connector_handler {
public:
	virtual void on_connect_success() = 0;
	virtual void on_connect_fail() = 0;
	virtual void on_disconnect() = 0;
	virtual void on_message(void * data, uint32_t length) = 0;
};

class connector : public noncopyable {
public:
	connector();
	virtual ~connector();

public:

	virtual bool init(struct event_base * base, std::string host, uint32_t port, connector_handler * handler);

	virtual bool connect(uint32_t timeout = 0);

	virtual void close();

	virtual void send(void *data, uint32_t length);

	virtual void do_recv();

	connector_handler * get_handler();

private:

	static void conn_readcb(struct bufferevent *bev, void *user_data);

	static void conn_writecb(struct bufferevent *bev, void *user_data);

	static void conn_eventcb(struct bufferevent *bev, short events, void *user_data)

private:

	uint32_t 								m_port;	
	connector_handler * 					m_conn_handler;
	struct event_base *						m_event_base;
	struct bufferevent * 					m_bufferevent;
	socket_message *        				m_socket_msg;
	std::string 							m_host;
};

} // namespace xlogic

#endif //__CONNECTOR_H__
