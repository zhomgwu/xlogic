
message_subscription::message_subscription() {

}

message_subscription::~message_subscription() {

}

static message_subscription * message_subscription::m_instance = nullptr;
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

void message_subscription::subscribe(uint32_t msg_id, agent * ag) {
    m_subscription.insert({msg_id, ag});
}

void message_subscription::unsubscribe(uint32_t msg_id, agent * ag) {
    auto pos = m_subscription.begin();
    while(pos != m_subscription.end()) {
        if (pos->first == msg_id && pos->second == ag) {
            m_subscription.erase(msg_id);
            break;
        }
    }
}

void message_subscription::unsubscribe(uint32_t msg_id) {
    m_subscription.erase(msg_id);
}

void message_subscription::unsubscribe(agent *ag) {
    auto pos = m_subscription.begin();
    while(pos != m_subscription.end()) {
        if (pos->second == ag) {
            pos = m_subscription.erase(msg_id);
        }
        else {
            pos++;
        }
    }
}

void message_subscription::get_subscription(uint32_t msg_id, std::vector<agent *> &agents);{
    auto pos_range = m_subscription.equal_range(msg_id);
    while (pos_range->first != pos_range->second) {
        agents.push_back(pos_range->second);
        pos_range++;
    }
}
