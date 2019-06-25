#ifndef __AGENT_H__
#define __AGENT_H__

#include "noncopyable.h"
#include "type_def.h"

XLOGIC_BEGIN

class message_processor;
class agent : public noncopyable {
public:
	agent(struct bufferevent *bev);
	virtual ~agent();

public:

	virtual void do_recv();

	virtual bool send(void * data, uint32_t len);

	struct bufferevent * get_bufferevent();

    message_processor * get_socket_message_processor();

private:
    char *                  m_buffer_read;
    message_processor *     m_msg_proc;
	struct bufferevent *	m_bufferevent;
};

XLOGIC_END

#endif // __AGENT_H__
