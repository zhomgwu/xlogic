#ifndef __AGENT_H__
#define __AGENT_H__

#include "noncopyable.h"

namespace xlogic {

#define DEFAULT_RECV_BUFFER_SIZE   65535

class agent : public noncopyable {
public:
	agent(struct bufferevent *bev);
	virtual ~agent();

public:

	virtual void do_recv();

	virtual bool send(void * data, uint32_t len);

	struct bufferevent * get_bufferevent() final;

private:

	char *					m_recv_buffer;
	uint32_t 				m_recv_length;
	uint32_t 				m_recv_buffer_size;
	struct bufferevent *	m_bufferevent;
};

} // namespace xlogic

#endif // __AGENT_H__
