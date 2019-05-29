#include "agent.h"

#define RECV_BUFFER_SIZE 4096

agent::agent(struct bufferevent *bev)
: m_buffer_read(nullptr)
, m_socket_msg(nullptr)
, m_bufferevent(bev) {
	m_buffer_read = (char *)malloc(RECV_BUFFER_SIZE);
	m_socket_msg = new socket_message();
}

agent::~agent() {
	if (m_buffer_read) {
		delete m_buffer_read;
		m_buffer_read = nullptr;
	}

	if (m_socket_msg) {
		delete m_socket_msg;
		m_socket_msg = nullptr;
	}
}

void agent::do_recv() {
	if (m_bufferevent) {
		size_t recv_length = 0;
		recv_length = bufferevent_read(m_bufferevent, m_buffer_read, RECV_BUFFER_SIZE);
		if (recv_length > 0) {
			m_socket_msg->append(m_buffer_read, recv_length);	
		}
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

socket_message * agent::get_socket_message() {
	return m_socket_msg;
}