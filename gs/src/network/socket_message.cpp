#include "socket_message.h"
#include <cstring>

#define MIN_SOCKET_BUFFER_SIZE 64

socket_message::socket_message()
: m_data(nullptr) 
, m_length(0)
, m_size(MIN_SOCKET_BUFFER_SIZE) {
    m_data = malloc(m_size);
}

socket_message::~socket_message() {
    if (m_data != nullptr) {
        free(m_data);
        m_data = nullptr;
    }
}

void *socket_message::raw_data() {
    return m_data;
}

uint32_t socket_message::size() {
    return m_size;
}

uint32_t socket_message::length() {
    return m_length;
}

void socket_message::append(void *data, uint32_t len) {
    uint32_t need_size = m_length + len;
    if (check_size(need_size)) {
        // log size not enough here
        return;
    }

    memcpy(m_data+m_length, data, len);
    m_length += len;
}

bool socket_message::get_data(void *dst, uint32_t len) {
    if (m_length < len) {
        return false;
    }

    memcpy(dst, m_data, len);
    m_length -= len;
    memmove(m_data, m_data+len, m_length);
    return true;
}

bool socket_message::check_size(uint32_t size) {
    if (size > m_size) {
        do {
            m_size *= 2;
        }
        while(size > m_size);
    }
    else if (size > 0 && size*2 < m_size){
        m_size /=2;
    }
    else {
        return true;
    }

    void *new_ptr = realloc(m_data, m_size)
    if (nullptr != new_ptr) {
        m_data = new_ptr;
        return true;
    }
    return false;
}
