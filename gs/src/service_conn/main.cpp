#include "logger_manager.h"
#include <thread>
#include <chrono>

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
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        count++;
    }
    logger_manager::get_instance()->stop_log();
}

int main(int argc, char *argv[]) {
    test_logger_manager();
    return 0;
}

