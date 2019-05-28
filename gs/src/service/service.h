#ifndef __SERVICE_H__
#define __SERVICE_H__

class work_dispatcher;
class service {
public:
    bool init(work_dispatcher *dispatcher) = 0;
    void handle(void *data, int len, void *userdata) = 0;
};

#endif //__SERVICE_H__
