#include "listener.h"
#include <string.h>
#include "agent.h"
#include "message_processor.h"

XLOGIC_BEGIN

listener::listener() 
: m_port(0)
, m_handler(nullptr)
, m_agent_maker(nullptr) {

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

void listener::set_agent_maker(agent_maker * maker) {
	m_agent_maker = maker;
}

listener_handler * listener::get_handler() {
	return m_handler;
}

agent* listener::new_agent(struct bufferevent *bev) {
	agent * ag = nullptr;
	if (m_agent_maker) {
		ag = m_agent_maker->new_agent(bev);
	} else {
		ag = new agent(bev);
	}
	m_agents.insert(std::make_pair(bev, ag));
	return ag;
}

agent *listener::find_agent(struct bufferevent *bev) {
	if (m_agents.find(bev) != m_agents.end()) {
		return m_agents[bev];
	}
	return nullptr;
}

void listener::delete_agent(agent * ag) {
	if (ag != nullptr) {
		struct bufferevent * bev = ag->get_bufferevent();
		m_agents.erase(bev);
		
		if (m_agent_maker) {
			m_agent_maker->delete_agent(ag);
		} else {
			delete ag;
		}
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

	agent *ag = my_listener->new_agent(bev);
	if (handler && ag) {
		handler->on_new_agent(ag);
	}
}

void listener::conn_readcb(struct bufferevent *bev, void *user_data) {
	/* The read callback is triggered when new data arrives in the input
     buffer and the amount of readable data exceed the low watermark
     which is 0 by default.*/
	USING_XLOGIC

	xlogic::listener *my_listener = (xlogic::listener *)user_data;
	agent *ag = my_listener->find_agent(bev);
	if (ag != nullptr) {
		ag->do_recv();
		// 尝试获得整包，获得整包后就处理
		void *entire_data = nullptr;
		int data_len = 0;
		message_processor *ag_proc = ag->get_socket_message_processor();
		if (ag_proc->get_entire_data(&entire_data, data_len)) {
			xlogic::listener_handler * handler = my_listener->get_handler();
			if (handler != nullptr) {
				handler->on_message(ag, entire_data, data_len);
			}
			// 数据用完丢弃
			ag_proc->drop_data(data_len);
		}
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
		my_listener->delete_agent(ag);
		bufferevent_free(bev);
	}
}

XLOGIC_END