#include "listener.h"
#include <string.h>
#include "agent.h"

XLOGIC_BEGIN

listener::listener() 
: m_port(0)
, m_handler(nullptr) {

}

listener::~listener() {

}

bool listener::init(struct event_base * base, uint16_t port, listener_handler *handler) {
	if (!base) {
		return false;
	}
	if (port <= 1024 || port >= 65535) {
		return false;
	}
	m_event_base = base;
	m_port = port;
	if (handler) {
		m_handler = handler;
	}
	return true;
}

bool listener::listen() {
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(m_port);

	m_listener = evconnlistener_new_bind(m_event_base, 
		listener::listener_cb, 
		(void *)this,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, 
	    -1, // backlog, -1 means default reasonable acceptable connection.
	    (struct sockaddr*)&sin, 
	    sizeof(sin));

	if (!m_listener) {
		return false;
	}
	return true;
}

listener_handler * listener::get_handler() {
	return m_handler;
}

agent* listener::new_agent(struct bufferevent *bev) {
	agent * ag = new agent(bev);
	if (ag) {
		m_agents.insert(std::make_pair(bev, ag));
		return ag;
	}
	return nullptr;
}

agent *listener::find_agent(struct bufferevent *bev) {
	if (m_agents.find(bev) != m_agents.end()) {
		return m_agents[bev];
	}
	return nullptr;
}

void listener::delete_agent(agent * ag) {
	if (ag) {
		struct bufferevent * bev;
		bev = ag->get_bufferevent();
		m_agents.erase(bev);
		delete ag;
	}
}

void listener::listener_cb(struct evconnlistener *listener, evutil_socket_t fd, 
		struct sockaddr *sa, int socklen, void *user_data) {
	struct event_base *base = evconnlistener_get_base(listener);
	xlogic::listener *my_listener = (xlogic::listener *)user_data;

	xlogic::listener_handler * handler = my_listener->get_handler();
	if (handler) {
		if (!handler->check_address(sa, socklen)) {
			return;
		}
	}

	struct bufferevent *bev;
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, listener::conn_readcb, listener::conn_writecb, listener::conn_eventcb, (void*)my_listener);
	bufferevent_enable(bev, EV_READ | EV_WRITE);

	agent *ag;
	ag = my_listener->new_agent(bev);
	if (handler) {
		handler->on_new_agent(ag);
	}
}

void listener::conn_readcb(struct bufferevent *bev, void *user_data) {
	/* The read callback is triggered when new data arrives in the input
     buffer and the amount of readable data exceed the low watermark
     which is 0 by default.*/
	xlogic::listener *my_listener = (xlogic::listener *)user_data;
	agent *ag = my_listener->find_agent(bev);
	if (ag) {
		ag->do_recv();
	}
}

void listener::conn_writecb(struct bufferevent *bev, void *user_data) {
	/* The write callback is triggered if the write buffer has been
     exhausted or fell below its low watermark.*/
	
}

void listener::conn_eventcb(struct bufferevent *bev, short events, void *user_data) {
	xlogic::listener *my_listener = (xlogic::listener *)user_data;

	agent *ag = my_listener->find_agent(bev);
	xlogic::listener_handler * handler = my_listener->get_handler();
	
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		if (handler) {
			handler->on_disconnect(ag);
		}
		delete_agent(bev);
		bufferevent_free(bev);
	}
}

XLOGIC_END