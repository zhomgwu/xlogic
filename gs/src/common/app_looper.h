#ifndef __APP_LOOPER_H__
#define __APP_LOOPER_H__

#include "type_def.h"

class app_looper {
public:
    virtual ~app_looper();

public:
    virtual void on_start() = 0;
    virtual void on_end() = 0;
    virtual void on_loading_begin() = 0;
    virtual void on_loading_end() = 0;
    virtual void on_update() = 0;
    virtual void on_sec(uint64_t ts) = 0;
};

#endif //__APP_LOOPER_H__
