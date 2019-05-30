
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

}

void message_subscription::unsubscribe(uint32_t msg_id, agent * ag) {

}

void message_subscription::unsubscribe(uint32_t msg_id) {

}

void message_subscription::unsubscribe(agent *ag) {

}

void message_subscription::get_subscription(uint32_t msg_id, std::vector<agent *> &agents);{

}
