#ifndef __POLLER_H__
#define __POLLER_H__

#include <string>
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "type_def.h"
#include "noncopyable.h"

XLOGIC_BEGIN

class listener;
class listener_handler;
class connector;
class connector_handler;
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
    listener * create_listener(uint16_t port, listener_handler *handler);
    connector * create_connector(std::string host, uint32_t port, connector_handler * handler);

private:
    struct event_base * m_evbase;
};

XLOGIC_END

#endif //__POLLER_H__
