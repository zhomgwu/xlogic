#ifndef __GAME_LOOPER_H__
#define __GAME_LOOPER_H__

#include "app_looper.h"

USING_XLOGIC

class game_looper : public app_looper {
public:
    virtual ~game_looper();

public:
    virtual void on_start();
    virtual void on_end();
    virtual void on_loading_begin();
    virtual void on_loading_end();
    virtual void on_update();
    virtual void on_sec(uint64_t ts);
};

#endif //__GAME_LOOPER_H__
