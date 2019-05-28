#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <event2/listener.h>

namespace xlogic {

class agent;
class listener_handler {
public:
	virtual bool check_address(struct sockaddr *sa, int socklen) = 0;
	virtual void on_new_agent(agent* ag) = 0;
	virtual void on_disconnect(agent* ag) = 0;
};

class listener : public noncopyable  {
public:
	listener();
	virtual ~listener();

public:

	virtual bool init(struct event_base * base, uint16_t port, listener_handler *handler);

	virtual bool listen();

	virtual listener_handler * get_handler();

	virtual agent* new_agent(struct bufferevent *bev);

	virtual agent *find_agent(struct bufferevent *bev);
	
	virtual void delete_agent(agent * ag);

private:

	static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, 
		struct sockaddr *sa, int socklen, void *user_data);

	static void conn_readcb(struct bufferevent *bev, void *user_data);

	static void conn_writecb(struct bufferevent *bev, void *user_data);

	static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);

private:

	uint16_t 								m_port;
	listener_handler *						m_handler;
	struct event_base *						m_event_base;
	struct evconnlistener *					m_listener;
	std::map<struct bufferevent *, agent*> 	m_agents;
};

}; // namespace xlogic

#endif // __LISTENER_H__
