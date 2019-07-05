#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "type_def.h"
#include "network.h"
#include "signal_handler.h"

USING_XLOGIC

enum ServerStatus {
    SS_OPENING = 1,
    SS_OPEN = 2,
    SS_WILL_CLOSE = 3,
    SS_CLOSING = 4,
    SS_CLOSE = 5,
};

struct server_config {
	uint16_t client_listener_port;
	uint16_t game_listener_port;
	uint16_t login_listener_port;
	uint16_t max_client;
};

class server : public signal_handler {
public:
	server();
	~server();

public:

	bool server_init(std::string conf_path);
	void server_run();
	void server_exit();

	virtual void on_signal(int signo);

private:

	bool init_server_config(std::string path);
	bool init_network();
	bool init_db();
	bool init_configurate();
	bool init_game();

	poller *get_poller();
	inner_listener *get_server_listener();

private:
	int m_status;
	poller * m_poller;										// 轮询器
	listener * m_client_listener;							// 客户端连接
	server_config m_config;
	std::map<int, inner_listener*> m_inner_listeners;		// 服务器连接
};

#endif // __SERVER_H__
