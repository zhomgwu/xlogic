#ifndef __GAME_LOOPER_H__
#define __GAME_LOOPER_H__

class game_looper {
public:
    void on_start();
    void on_end();
    void on_loading_begin();
    void on_loading_end();
    void on_update();
    void on_sec();
};

#endif 
