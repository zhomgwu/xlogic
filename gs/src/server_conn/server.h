#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include "type_def.h"

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

private:

};

#endif // __SERVER_H__
