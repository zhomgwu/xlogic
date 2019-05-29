#ifndef __AGENT_H__
#define __AGENT_H__

#include "noncopyable.h"

namespace xlogic {

class socket_message;
class agent : public noncopyable {
public:
	agent(struct bufferevent *bev);
	virtual ~agent();

public:

	virtual void do_recv();

	virtual bool send(void * data, uint32_t len);

	struct bufferevent * get_bufferevent();

    socket_message * get_socket_message();

private:
    char *                  m_buffer_read;
    socket_message *        m_socket_msg;
	struct bufferevent *	m_bufferevent;
};

} // namespace xlogic

#endif // __AGENT_H__
