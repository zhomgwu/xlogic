#include "message_subscription.h"

message_subscription::message_subscription() {

}

message_subscription::~message_subscription() {

}

message_subscription * message_subscription::m_instance = nullptr;
message_subscription * message_subscription::get_instance() {
    if (!m_instance) {
        m_instance = new message_subscription();
    }
    return m_instance;
}

void message_subscription::destroy() {
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void message_subscription::subscribe(uint32_t msg_id, isocket *sock) {
    m_subscription.insert({msg_id, sock});
}

void message_subscription::unsubscribe(uint32_t msg_id, isocket *sock) {
    auto pos = m_subscription.begin();
    while(pos != m_subscription.end()) {
        if (pos->first == msg_id && pos->second == sock) {
            m_subscription.erase(msg_id);
            break;
        }
    }
}

void message_subscription::unsubscribe(uint32_t msg_id) {
    m_subscription.erase(msg_id);
}

void message_subscription::unsubscribe(isocket *sock) {
    auto pos = m_subscription.begin();
    while(pos != m_subscription.end()) {
        if (pos->second == sock) {
            pos = m_subscription.erase(pos);
        }
        else {
            pos++;
        }
    }
}

void message_subscription::get_subscription(uint32_t msg_id, std::vector<isocket *> &socks) {
    auto pos_range = m_subscription.equal_range(msg_id);
    for (auto i = pos_range.first; i != pos_range.second; ++i) {
        socks.push_back(i->second);
    }
}
