#ifndef __SERVER_H__
#define __SERVER_H__

struct server_config {
	uint16_t port;
	uint16_t max_client;
};

class server {
public:
	server();
	~server();

public:

	void server_init();

	void server_run();

	void server_exit();
};

#endif // __SERVER_H__
