#include "agent.h"

agent::agent(struct bufferevent *bev)
: m_recv_buffer(nullptr) 
, m_recv_length(0) 
, m_recv_buffer_size(0)
, m_bufferevent(bev) {
	m_recv_buffer = (char *)malloc(DEFAULT_RECV_BUFFER_SIZE);
	m_recv_buffer_size = DEFAULT_RECV_BUFFER_SIZE;
}

agent::~agent() {
	if (m_recv_buffer) {
		delete m_recv_buffer;
		m_recv_buffer = nullptr;
	}
}

void agent::do_recv() {
	if (bufferevent) {
		size_t recv = 0;
		recv = bufferevent_read(m_bufferevent, m_recv_buffer+m_recv_length, m_recv_buffer_size-m_recv_length);
		
		

	}
}

bool agent::send(void * data, uint32_t len) {
	if (0 != bufferevent_write(m_bufferevent, data, len)) {
		return false;
	}
	return true;
}

struct bufferevent * agent::get_bufferevent() {
	return m_bufferevent;
}