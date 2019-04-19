
#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <unordered_map>

class listener_delegate {
public:
	virtual void listen_callback(uint32_t fd, void *data, uint32_t len) = 0;
};

class listener {
public:
	listener();
	virtual ~listener(); 

public:

	virtual bool init(uint16_t m_port, listener_delegate *delegate);

	virtual bool listen();

	virtual void run_accept();

private:
	uint16_t m_port;
	listener_delegate *m_delegate;
};

#endif // __LISTENER_H__
