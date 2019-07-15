#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "type_def.h"
#include "network.h"
#include "signal_handler.h"
#include "game_looper.h"

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
	virtual ~server();

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

	server_config *get_server_config();
	poller *get_poller();
	
private:
	server_config m_config;									// 服务器配置
	int m_status;											// 服务器状态
	game_looper * m_app_looper;								// 游戏固定回调
	poller * m_poller;										// 网络轮询器

	connector * m_conn_connector;							// 网关服代理
};

#endif // __SERVER_H__
