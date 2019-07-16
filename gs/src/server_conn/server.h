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
	std::string game_host;
	uint16_t game_port;
	std::string login_host;
	uint16_t login_port;
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
	listener *get_server_listener();

private:
	server_config m_config;									// 服务器配置
	int m_status;											// 服务器状态
	game_looper * m_app_looper;								// 游戏固定回调
	poller * m_poller;										// 网络轮询器

	listener * m_client_listener;							// 客户端监听器
	connector * m_game_connector;							// 游戏服连接器
	connector * m_login_connector;							// 登录服连接器
};

#endif // __SERVER_H__
