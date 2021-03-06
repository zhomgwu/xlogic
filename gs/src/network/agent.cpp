#include "agent.h"
#include <stdlib.h>
#include "message_processor.h"

#define RECV_BUFFER_SIZE 4096

XLOGIC_BEGIN


agent::agent(struct bufferevent *bev)
: m_buffer_read(nullptr)
, m_msg_proc(nullptr)
, m_bufferevent(bev) {
	m_buffer_read = (char *)malloc(RECV_BUFFER_SIZE);
	m_msg_proc = new message_processor();
}

agent::~agent() {
	if (m_buffer_read) {
		delete m_buffer_read;
		m_buffer_read = nullptr;
	}

	if (m_msg_proc) {
		delete m_msg_proc;
		m_msg_proc = nullptr;
	}
}

void agent::do_recv() {
	if (m_bufferevent) {
		size_t recv_length = 0;
		recv_length = bufferevent_read(m_bufferevent, m_buffer_read, RECV_BUFFER_SIZE);
		if (recv_length > 0) {
			m_msg_proc->append(m_buffer_read, recv_length);	
		}
	}
}

void agent::close() {
	if (m_bufferevent) {
        bufferevent_free(m_bufferevent);
        m_bufferevent = nullptr;
    }
}

bool agent::send(void * data, int length) {
	if (0 != bufferevent_write(m_bufferevent, data, (size_t)length)) {
		return false;
	}
	return true;
}

struct bufferevent * agent::get_bufferevent() {
	return m_bufferevent;
}

message_processor * agent::get_socket_message_processor() {
	return m_msg_proc;
}

XLOGIC_END