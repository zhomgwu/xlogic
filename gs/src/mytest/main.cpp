#include <thread>
#include <chrono>
#include <unistd.h> // daemon
#include "type_def.h"
#include "logger_manager.h"
#include "listener.h"
#include "poller.h"
#include "get_opt.h"
#include "yaml-cpp/yaml.h"

void test_logger_manager() {
    logger_manager::get_instance()->init_log("./log");
    logger_manager::get_instance()->start_log();
    int count = 0;
    while(count < 10) {
        LOGINFO("LOG INFO");
        LOGDEBUG("LOG DEBUG");
        LOGERROR("LOG ERROR");
        LOGFATAL("LOG FATAL");
        LOGWARN("LOG WARN");

        LOGINFO("LOG INFO %d hello", 123123);
        LOGDEBUG("LOG DEBUG %d hello", 123123);
        LOGERROR("LOG ERROR %d hello", 123123);
        LOGFATAL("LOG FATAL %d hello", 123123);
        LOGWARN("LOG WARN %d hello", 123123);
        count++;
    }
    //logger_manager::get_instance()->stop_log();
}

void test_network() {
    USING_XLOGIC
    poller * pl = new poller();
    if (!pl->init()) {
        delete pl;
        return;
    }
    listener * ls = new listener();
    if (!ls->init(pl->get_event_base(), 12767, nullptr)) {
        LOGERROR("listen %d fail", 12767); 
        delete pl;
        delete ls;
        return;
    }
    ls->listen();
    pl->run();
    delete pl;
    delete ls;
}

void test_yaml() {
    YAML::Node node = YAML::LoadFile("test_config.yml");
    if (!node.IsDefined()) {
        LOGERROR("yaml file error");
        return;
    }
    LOGDEBUG("size %lu", node.size());
    LOGDEBUG("node %d", node["server_conn"]["port"][0].as<int>());
    LOGDEBUG("node %d", node["server_conn"]["port"][1].as<int>());
    // LOGDEBUG("node %d", node["server_conn"]["port"][2]);

    if (node["server_conn"]["port"][2].IsDefined()) {
        LOGDEBUG("========== exist");
    } else {
        LOGDEBUG("========== no!");
    }

    // for (auto &port : node["server_conn"]["port"].as<std::list<int>>()) {
    //     LOGDEBUG("list print port %d", port);
    // }

}

int main(int argc, char *argv[]) {
    get_opt opt(argc, (const char**)argv);
    // 后台启动
    if (opt.has("-d")) {
        daemon(1, 1);
    }
    
    if (opt.has("-log")) {
        test_logger_manager();    
    } else {        
        INIT_LOG("./log");
        START_LOG();
    }

    if (opt.has("-network")) {
        test_network();    
    }
    if (opt.has("-yaml")) {
        test_yaml();
    }
    
    return 0;
}
