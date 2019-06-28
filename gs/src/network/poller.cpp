#include "poller.h"

XLOGIC_BEGIN

poller::poller() 
: m_evbase(nullptr) {

}

poller::~poller() {

}

bool poller::init() {
    m_evbase = event_base_new();
    if (!m_evbase) {
        return false;
    }
    return true;
}

void poller::run() {
    if (m_evbase) {
        event_base_dispatch(m_evbase);
    }
}

void poller::step() {
    if (m_evbase) {
        event_base_loop(m_evbase, EVLOOP_ONCE | EVLOOP_NONBLOCK);
    }
}

void poller::stop() {
    if (m_evbase) {
        // NULL to exit after running all currently active events
        event_base_loopexit(m_evbase, nullptr);
        event_base_free(m_evbase); 
        m_evbase = nullptr;  
    }
}

struct event_base *poller::get_event_base() {
    return m_evbase;
}

listener * poller::create_listener(uint16_t port, listener_handler *handler) {
    return nullptr;
}

connector * poller::create_connector(std::string host, uint32_t port, connector_handler * handler) {
    return nullptr;
}

XLOGIC_END
