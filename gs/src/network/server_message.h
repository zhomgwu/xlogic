#ifndef __SERVER_MESSAGE_H__
#define __SERVER_MESSAGE_H__

#include "type_def.h"

enum INNER_MESSAGE {
    INNER_NULL                  = 0,        // 无
    INNER_SOCK_NEW              = 1,        // 新连接
    INNER_SOCK_CLOSE            = 2,        // 连接关闭
    INNER_SOCK_AUTH             = 3,        // 连接认证
    
    INNER_MSG_FORWARD           = 4,        // 转发
    INNER_MSG_BROADCAST         = 5,        // 广播
    INNER_MSG_SUBSCRIBE         = 6,        // 订阅

    INNER_SERVER_CLOSE          = 100,      // 服务器关闭
    INNER_MAX                   = 1000      // 内部最大消息id
};

#pragma pack(push)      // 保存对齐状态
#pragma pack(1)         // 1 bytes对齐

struct user_info {
    uint64_t user_id;           // 账号id
    uint64_t player_id;         // 区id
    uint32_t session_id;        // 会话id
};

// 客户端与服务器的包头
struct message_head {
    uint16_t length;            // 消息长度，包括头部
    uint16_t message_id;        // 消息id
};

// 特殊包头例子，继承于message_head
struct special_message_head : public message_head {
    uint32_t encrypt_key;
};

// 服务器与服务器的包头
struct inner_message_head : public message_head {

};

struct message_sock_new : public inner_message_head {
    uint32_t session_id;
    message_sock_new() {
        message_id = INNER_SOCK_NEW;
        length = sizeof(message_sock_new);
        session_id = 0;
    }
};

struct message_sock_close : public inner_message_head {
    uint32_t session_id;
    message_sock_close() {
        message_id = INNER_SOCK_CLOSE;
        length = sizeof(message_sock_close);
        session_id = 0;
    }
};

struct message_sock_auth : public inner_message_head {
    user_info usr_info;
    message_sock_auth() {
        message_id = INNER_SOCK_AUTH;
        length = sizeof(message_sock_auth);
        usr_info.user_id = 0;
        usr_info.player_id = 0;
        usr_info.session_id = 0;
    }

    void set_user_info(uint64_t user_id, uint64_t player_id, uint32_t session_id) {
        usr_info.user_id = user_id;
        usr_info.player_id = player_id;
        usr_info.session_id = session_id;
    }
};

struct message_forward : public inner_message_head {
    uint32_t session_id;
    message_forward() {
        message_id = INNER_MSG_FORWARD;
        length = sizeof(message_forward);
        session_id = 0;
    }
};

struct message_broadcast : public inner_message_head {
    uint32_t broadcast_count;
    message_broadcast() {
        message_id = INNER_MSG_BROADCAST;
        length = sizeof(message_broadcast);
        broadcast_count = 0;
    }

    void set_broadcast_size(uint32_t b_size) {
        broadcast_count = b_size;
    }
};

struct message_subscribe : public inner_message_head {
    uint32_t subscribe_id;  //订阅id
    message_subscribe() {
        message_id = INNER_MSG_SUBSCRIBE;
        length = sizeof(message_subscribe);
        subscribe_id = 0;
    }
};

struct message_server_close : public inner_message_head {
    message_server_close() {
        message_id = INNER_SERVER_CLOSE;
        length = sizeof(message_server_close);
    }
};

#pragma pack(pop)       //恢复对齐状态

// 打包函数
static message_sock_new * make_message_sock_new(uint32_t session_id);
static message_sock_close * make_message_sock_close(uint32_t session_id);
static message_sock_auth * make_message_sock_auth(uint64_t user_id, uint64_t player_id, uint32_t role_id, uint32_t session_id);
static message_forward * make_message_forward(uint32_t session_id, void *data, uint32_t len);
static message_broadcast * make_message_broadcast(uint64_t *session_array, uint32_t count, void *data, uint32_t len);
static message_server_close * make_message_server_close();
static void destroy_message(inner_message_head *msg);

#endif // __SERVER_MESSAGE_H__
