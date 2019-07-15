#include <string>
#include <iostream>
#include "get_opt.h"
#include "type_def.h"
#include "network.h"
#include "logger_manager.h"
#include "server_message.h"

USING_XLOGIC

using namespace std;

class my_handler : public connector_handler {
public:
    virtual void on_connect_success(connector *conn) override {

        client_message_head head;
        head.length = sizeof(head);
        head.message_id = 12311;
        conn->send(&head, sizeof(head));

        LOGDEBUG("on connect success");
    }
	
    virtual void on_connect_fail(connector *conn) override {
        LOGDEBUG("on connect success");
    }

	virtual void on_disconnect(connector *conn) override {
        LOGDEBUG("on connection disconnect");
    }

	virtual void on_message(connector *conn, void * data, uint32_t length) override {
        client_message_head *head = (client_message_head*)data;

        LOGDEBUG("on message %d", length);
        LOGDEBUG("on message :%d, message id:%d", head->length, head->message_id );
        conn->send(data, length);
    }
};

int main(int argc, char *argv[]) {
    logger_manager::get_instance()->init_log("./robotlog");
    logger_manager::get_instance()->start_log();

    poller * pl = new poller();
    if (!pl->init()) {
        delete pl;
        return -1;
    }

    connector * conn = new connector();
    if (!conn->init(pl->get_event_base(), "127.0.0.1", 6001, new my_handler())) {
        LOGDEBUG("connect fail");
        return -1;
    }
    conn->connect();
    pl->run();
    
    logger_manager::get_instance()->stop_log();
    return 0;
}
