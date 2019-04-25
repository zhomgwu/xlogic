#ifndef __LISTENER_H__
#define __LISTENER_H__

class listener_handler {
public:
	virtual void listen_callback(uint32_t fd, void *data, uint32_t len) = 0;
	virtual void listen_error(int error_no) = 0;
};

class listener {
public:
	listener();
	virtual ~listener(); 

public:

	virtual bool init(uint16_t m_port, listener_handler *handler);

	virtual void listen();

	virtual void run_accept();

private:
	uint16_t m_port;
	listener_handler *m_delegate;
};

#endif // __LISTENER_H__
