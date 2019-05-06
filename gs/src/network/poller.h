#ifndef __POLLER_H__
#define __POLLER_H__

class poller {
public:
    poller();
    ~poller();

public:
    bool init();
    void run();
    void step();
    void stop();

    struct event_base *get_event_base();

private:

    struct event_base * m_evbase;
};

#endif //__POLLER_H__
