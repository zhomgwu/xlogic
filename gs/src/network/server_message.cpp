#include "server_message.h"
#include <stdlib.h>
#include <string.h>

static message_sock_new * make_message_sock_new(uint32_t session_id) {
    uint32_t length = sizeof(message_sock_new);
    message_sock_new * msg = (message_sock_new *)malloc(length);
    msg->length = length;
    msg->session_id = session_id;
    return msg;
}

static message_sock_close * make_message_sock_close(uint32_t session_id) {
    uint32_t length = sizeof(message_sock_close);
    message_sock_close * msg = (message_sock_close *)malloc(length);
    msg->length = length;
    msg->session_id = session_id;
    return msg;
}

static message_sock_auth * make_message_sock_auth(uint64_t user_id, uint64_t player_id, uint32_t session_id) {
    uint32_t length = sizeof(message_sock_auth);
    message_sock_auth * msg = (message_sock_auth *)malloc(length);
    msg->length = length;
    msg->set_user_info(user_id, player_id, session_id);
    return msg;
}

static message_forward * make_message_forward(uint32_t session_id, void *data, uint32_t len) {
    // 头部 + 转发数据
    uint32_t length = sizeof(message_forward) + len;
    char * msg_data = (char *)malloc(length);
    message_forward * msg = (message_forward *)msg_data;
    msg->length = length;
    msg->session_id = session_id;
    memcpy(msg_data+sizeof(message_forward), data, len);
    return msg;
}

static message_broadcast * make_message_broadcast(uint64_t *session_array, uint32_t count, void *data, uint32_t len) {
    // 头部 + session数组 + 广播数据
    uint32_t length = sizeof(message_broadcast) + (count * sizeof(uint64_t)) + len;
    char * msg_data = (char *)malloc(length);
    message_broadcast * msg = (message_broadcast * )data;
    msg->length = length;
    msg->broadcast_count = count;
    if (nullptr == session_array && count != 0) {
        msg->broadcast_count = 0;
    }
    if (msg->broadcast_count != 0) {
        memcpy(msg_data+sizeof(message_broadcast), session_array, count * sizeof(uint64_t));
    }
    uint32_t offset = sizeof(message_broadcast) + count * sizeof(uint64_t);
    memcpy(msg_data+offset, data, len);
    return msg;
}

static message_server_close * make_message_server_close() {
    uint32_t length = sizeof(message_sock_auth);
    message_server_close * msg = (message_server_close *)malloc(length);
    msg->length = length;
    return msg;
}

static void destroy_message(message_head *msg) {
    if (msg) {
        free(msg);
    }
}
