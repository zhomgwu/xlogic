#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

#include <unordered_map>

class player;
class player_manager {
private:
    player_manager();
    ~player_manager();

public:
    static player_manager * get_instance();
    static void destroy();

    void on_login(uint64_t player_id);
    void on_logout(uint64_t player_id);
    void on_sec(uint64_t player_id, uint64_t ts);
    void on_disconnect(uint64_t player_id, uint64_t ts);
    void on_day_reset(uint64_t player_id, uint64_t ts);

    player *get_player(uint64_t player_id);

    player* new_player();
    void save_player(uint64_t player_id);
    void save_player(player * pr);

private:
    static player_manager*                   m_instance;
    std::unordered_map<uint64_t, player*>    m_players;
};

#endif //__PLAYER_MANAGER_H__
