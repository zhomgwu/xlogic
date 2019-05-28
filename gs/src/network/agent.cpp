#include "agent.h"

agent::agent(struct bufferevent *bev)
: m_socket_msg(nullptr)
, m_bufferevent(bev) {
	m_socket_msg = new socket_message();
}

agent::~agent() {
	if (m_socket_msg) {
		delete m_socket_msg;
		m_socket_msg = nullptr;
	}
}

void agent::do_recv() {
	if (m_bufferevent) {
		size_t recv_length = 0;
		size_t recv_data_size = 4096;
		void *recv_data = malloc(recv_data_size);
		recv_length = bufferevent_read(m_bufferevent, recv_data, recv_data_size);

		m_socket_msg->append(recv_data, recv_length);

		free(recv_data);
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