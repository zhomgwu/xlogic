#include <string>
#include <iostream>
#include "get_opt.h"
#include "type_def.h"
#include "network.h"
#include "logger_manager.h"

USING_XLOGIC

using namespace std;

class my_handler : public connector_handler {
public:
    virtual void on_connect_success() override {
        LOGDEBUG("on connect success");
    }
	
    virtual void on_connect_fail() override {
        LOGDEBUG("on connect success");
    }

	virtual void on_disconnect() override {
        LOGDEBUG("on connect disconnect");
    }

	virtual void on_message(void * data, uint32_t length) override {
        LOGDEBUG("on message %d", length);
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
    if (!conn->init(pl->get_event_base(), "127.0.0.1", 12767, new my_handler())) {
        LOGDEBUG("connect fail");
        return -1;
    }
    conn->connect();
    pl->run();
    
    logger_manager::get_instance()->stop_log();
    return 0;
}
