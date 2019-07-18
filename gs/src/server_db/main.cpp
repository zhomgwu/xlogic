#include <string>
#include <unistd.h> // daemon
#include "type_def.h"
#include "logger_manager.h"
#include "server.h"
#include "get_opt.h"
#include "app_utility.h"

int main(int argc, char *argv[]) {
    get_opt opt(argc, (const char**)argv);
    // 后台启动
    if (opt.has("-d")) {
        daemon(1, 1);
    }
    // 记录pid
    std::string pid_name = argv[0];
    pid_name+= ".pid";
    if (!util::lock_and_record_pid(pid_name)) {
        return -1;
    }
    // 先初始化日志
    if (!opt.has("-logpath")) {
        INIT_LOG("./log");
    } else {
        INIT_LOG(opt["-logpath"]);
    }
    START_LOG();
    // 必须要有服务器配置
    if (!opt.has("-config")) {
        LOGERROR("Must specify configuration for server: \n\t-config name.yml");
        return -1;
    }

    std::string config = opt["-config"];
    server * srv = new server();
    if (!srv->server_init(config)) {
        SAFE_DELETE(srv);
        return -1;
    }
    srv->server_run();
    srv->server_exit();
    SAFE_DELETE(srv);
    STOP_LOG();
    return 0;
}
