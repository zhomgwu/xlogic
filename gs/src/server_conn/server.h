#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "type_def.h"
#include "poller.h"
#include "inner_listener.h"
#include "listener.h"

USING_XLOGIC

struct server_config {
	uint16_t port;
	uint16_t max_client;
	
};

class server {
public:
	server();
	~server();

public:

	bool server_init(std::string conf_path);
	void server_run();
	void server_exit();

private:

	bool init_log();
	bool init_network();
	bool init_configurate();
	bool init_db();
	bool init_game();

	poller *get_poller();
	inner_listener *get_server_listener();

private:

	std::map<int, inner_listener*> m_inner_listeners;		// 服务器连接
	poller * m_poller;										// 轮询器
	listener * m_client_listener;							// 客户端连接
};

#endif // __SERVER_H__
