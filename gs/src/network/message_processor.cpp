#include "message_processor.h"
#include <string.h>
#include <stdlib.h>
#include "socket_message_queue.h"
#include "server_message.h"

#define MIN_BUFFER_SIZE         64
#define SHRINK_BUFFER_SIZE      32768

XLOGIC_BEGIN

message_processor::message_processor()
: m_data(nullptr) 
, m_length(0)
, m_size(MIN_BUFFER_SIZE) {
    m_data = (char *)malloc(m_size);
}

message_processor::~message_processor() {
    if (m_data != nullptr) {
        free(m_data);
        m_data = nullptr;
    }
}

void *message_processor::raw_data() {
    return m_data;
}

uint32_t message_processor::size() {
    return m_size;
}

uint32_t message_processor::length() {
    return m_length;
}

void message_processor::append(void *data, uint32_t len) {
    uint32_t need_size = m_length + len;
    if (!check_size(need_size)) {
        // log size not enough here
        return;
    }

    memcpy(m_data+m_length, data, len);
    m_length += len;

    socket_message_queue *queue = socket_message_queue::get_instance();
    uint32_t offset = 0;

    do {
        if (m_length < sizeof(message_head)) {
            // head incomplete
            break;
        }
        
        uint32_t msg_len = 0;
        message_head *msg_head = (message_head*)m_data;
        msg_len = msg_head->length;
        if (m_length < msg_len) {
            // package incomplete
            break;
        }
        // 分离单个消息
        socket_message * msg = socket_message_queue::new_socket_message(m_data+offset, msg_len);
        queue->push(msg);
        
        m_length -= msg_len;
        offset += msg_len;
    }while(false);
    // 将数据全部移到头部
    if (offset > 0) {
        memmove(m_data, m_data+offset, m_length);    
    }
}

bool message_processor::get_data(void *dst, uint32_t len) {
    if (m_length < len) {
        return false;
    }

    memcpy(dst, m_data, len);
    m_length -= len;
    memmove(m_data, m_data+len, m_length);
    return true;
}

bool message_processor::check_size(uint32_t size) {
    if (size > m_size) {
        do {
            m_size *= 2;
        }
        while(size > m_size);
    }
    else if (m_size > SHRINK_BUFFER_SIZE && size*2 < m_size) {
        // shrink m_size in case larger than SHRINK_BUFFER_SIZE
        m_size /= 2;
    }
    else {
        return true;
    }

    char *new_ptr = (char *)realloc(m_data, m_size);
    if (nullptr != new_ptr) {
        m_data = new_ptr;
        return true;
    }
    return false;
}

XLOGIC_END
