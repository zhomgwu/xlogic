#ifndef __SESSION_MANAGER_H__
#define __SESSION_MANAGER_H__

class session_manager {
private:
    session_manager();
    ~session_manager();

public:
    static session_manager *get_instance();
    static void destroy();

    void set_session(uint32_t session_id, uint64_t player_id);

private:
    static session_manager *m_instance;
    std::map<uint32_t, uint64_t> m_session2player;
};

#endif //__SESSION_MANAGER_H__
