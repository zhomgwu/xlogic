#ifndef _SIGNAL_HANDLER_H__
#define _SIGNAL_HANDLER_H__

#include <set>

class signal_handler {
public:
	virtual void on_signal(int signo) = 0;
};

class signal_register {
private:
	signal_register();
	~signal_register();

public:
	static signal_register *get_instance();
	static void destroy();

public:

	bool init();

	void addregister(signal_handler *handler);

	void unregister(signal_handler *handler);

	std::set<signal_handler *>& get_handlers();

	static void signal_handler(int signo);

private:
	static signal_register * m_instance;
	std::set<signal_handler *>  m_handlers;
};

#endif //_SIGNAL_HANDLER_H__
