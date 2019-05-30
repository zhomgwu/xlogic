#include "socket_message_queue.h"

socket_message_queue::socket_message_queue() {

}

socket_message_queue::~socket_message_queue() {

}

socket_message_queue *socket_message_queue::m_instance = nullptr;
socket_message_queue *socket_message_queue::get_instance() {
    if (!m_instance) {
        m_instance = new socket_message_queue();
    }
    return m_instance;
}

void socket_message_queue::destroy() {
    if (m_instance!= nullptr) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void socket_message_queue::push(socket_message * msg) {
    m_messages.push(msg);
}

socket_message * socket_message_queue::pop() {
    return m_messages.pop();
}

std::queue<socket_message *> & get_messages() {
    return m_messages;
}

uint32_t socket_message_queue::message_count() {
    return m_messages.size();
}
