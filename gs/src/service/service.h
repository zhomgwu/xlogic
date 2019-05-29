#ifndef __SERVICE_H__
#define __SERVICE_H__

class service {
public:
    bool service_init() = 0;
    void service_run() = 0;
    void service_exit() = 0;
};

#endif //__SERVICE_H__
