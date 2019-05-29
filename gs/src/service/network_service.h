#ifndef __NETWORK_SERVICE_H__
#define __NETWORK_SERVICE_H__

class network_service {
public:
    network_service();
    ~network_service();

public:
    bool service_init();
    void service_run();
    void service_exit();
};

#endif //__NETWORK_SERVICE_H__
