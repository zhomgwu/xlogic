#include "signal_handler.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int		signo;
	char*	signame;
	char*	name;
	void (*handler)(int signo);
}srv_signal_t;

srv_signal_t signals[] = {
	{ SIGUSR1,	(char*)"SIGUSR1",			(char*)"",			signal_register::signal_handler },	/// SIGUSR1: kill -10 $pid
	{ SIGUSR2,	(char*)"SIGUSR2",			(char*)"",			signal_register::signal_handler },	/// SIGUSR1: kill -12 $pid

	{ SIGHUP,	(char*)"SIGHUP",			(char*)"",			signal_register::signal_handler },	
	{ SIGWINCH,	(char*)"SIGWINCH",			(char*)"",			signal_register::signal_handler },
	{ SIGTERM,	(char*)"SIGTERM",			(char*)"",			signal_register::signal_handler },
	{ SIGQUIT,	(char*)"SIGQUIT",			(char*)"",			signal_register::signal_handler },
	
	{ SIGALRM,	(char*)"SIGALRM",			(char*)"",			signal_register::signal_handler },
	{ SIGINT,	(char*)"SIGINT",			(char*)"",			signal_register::signal_handler },
	{ SIGIO,	(char*)"SIGIO",				(char*)"",			signal_register::signal_handler },
	{ SIGCHLD,	(char*)"SIGCHLD",			(char*)"",			signal_register::signal_handler },
	{ SIGSYS,	(char*)"SIGSYS, SIG_IGN",	(char*)"",			SIG_IGN },
	{ SIGPIPE,	(char*)"SIGPIPE, SIG_IGN",	(char*)"",			SIG_IGN },
	{ 0,		NULL,						(char*)"",			NULL }
};

signal_register::signal_register() {

}

signal_register::~signal_register() {

}

signal_register *signal_register::m_instance = NULL;
signal_register *signal_register::get_instance() {
	if (m_instance == NULL) {
		m_instance = new signal_register();
	}
	return m_instance;
}

void signal_register::destroy() {
	if (m_instance != NULL) {
		delete m_instance;
		m_instance = NULL;
	}
}

bool signal_register::init() {
	srv_signal_t*		sig;
	struct sigaction	sa;

	for (sig = signals; sig->signo != 0; sig++) {
		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = sig->handler;
		sigemptyset(&sa.sa_mask);
		if (sigaction(sig->signo, &sa, NULL) == -1) {
			return false;
		}
	}
	return true;
}

void signal_register::register_handler(SignalHandler *handler) {
	if (m_handlers.find(handler) != m_handlers.end()) {
		return;
	}
	m_handlers.insert(handler);
}

void signal_register::unregister(SignalHandler *handler) {
	if (m_handlers.find(handler) != m_handlers.end()) {
		m_handlers.erase(handler);
	}
}

std::set<SignalHandler *>& signal_register::get_handlers() {
	return m_handlers;
}

void signal_register::signal_handler(int signo) {
	signal_register *reg = signal_register::get_instance();
	std::set<SignalHandler *>& handlers = reg->get_handlers();
	for (std::set<SignalHandler *>::iterator iter = handlers.begin(); 
		iter != handlers.end(); ++iter) {
		if (*iter != NULL) {
			(*iter)->on_signal(signo);
		}
	}
}
