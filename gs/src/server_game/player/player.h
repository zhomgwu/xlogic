#ifndef __PLAYER_H___
#define __PLAYER_H___ 

class player {
public:
    player();
    ~player();

public:
    
    bool init();
    bool send2client(void *data, int len);
  
private:

    uint32_t m_session_id;
};

#endif