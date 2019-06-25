#ifndef __POLLER_H__
#define __POLLER_H__

#include "event2/bufferevent.h"
#include "event2/event.h"
#include "type_def.h"
#include "noncopyable.h"

XLOGIC_BEGIN

class poller : public noncopyable {
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

XLOGIC_END

#endif //__POLLER_H__
