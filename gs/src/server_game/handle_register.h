#ifndef __HANDLE_REGISTER__H__
#define __HANDLE_REGISTER__H__

#include <unordered_map>
#include <functional>
#include "type_def.h"

class player;

typedef std::function<void(player*, void *, int)> player_handler_func;
typedef std::function<void(void *, int)> handler_func;

class handle_register {
private:
    handle_register();
    ~handle_register();

public:
    static handle_register * get_instance();
    static void destroy();

    void add_player_handle(uint32_t cmd, player_handler_func func);
    void add_handle(uint32_t cmd, handler_func func);

    void dispatch(void *data, int len);

private:
    static handle_register * m_instance;

    std::unordered_map<uint32_t, player_handler_func>       m_player_handler;
    std::unordered_map<uint32_t, handler_func>              m_handler;
};


#define ADD_PLAYER_HANDLE(CMD, HANDLER) handle_register::get_instance()->add_player_handle(CMD, HANDLER)
#define ADD_HANDLE(CMD, HANDLER)        handle_register::get_instance()->add_handle(CMD, HANDLER);

#endif // __HANDLE_REGISTER__H__
