#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

namespace xlogic {

class connector_handler {
public:
	virtual void on_connect_success() = 0;
	virtual void on_connect_fail() = 0;
	virtual void on_disconnect() = 0;
	virtual void on_message(void * data, uint32_t length) = 0;
};

class connector {
public:
	connector();
	~connector();

public:

	virtual bool init(struct event_base * base, std::string host, uint32_t port, connector_handler * handler, bool block = false);

	virtual bool connect();

	virtual void send(void *data, uint32_t length);

private:

	connector_handler * m_conn_handler;
};

} // namespace xlogic

#endif //__CONNECTOR_H__
