#ifndef __MESSAGE_DEF_H__
#define __MESSAGE_DEF_H__

enum INNER_MESSAGE {
    INNER_NULL                  = 0,        // 无
    INNER_SOCK_NEW              = 1,        // 新连接
    INNER_SOCK_CLOSE            = 2,        // 连接关闭
    INNER_SOCK_AUTH             = 3,        // 连接认证
    
    INNER_MSG_FORWARD           = 4,        // 转发
    INNER_MSG_BROADCAST         = 5,        // 广播

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

struct message_head {
    uint16_t length;            // 消息长度，包括头部
    uint16_t message_id;        // 消息id
};

struct message_sock_new : public message_head {
    uint32_t session_id;
    message_sock_new() {
       message_id = INNER_SOCK_NEW;
       length = sizeof(message_sock_new);
       session_id = 0;
    }
};

struct message_sock_close : public message_head {
    uint32_t session_id;
    message_sock_close() {
       message_id = INNER_SOCK_CLOSE;
       length = sizeof(message_sock_close);
       session_id = 0;
    }
};

struct message_sock_auth : public message_head {
    user_info usr_info;
    message_sock_auth() {
       message_id = INNER_SOCK_AUTH;
       length = sizeof(message_sock_auth);
    }

    void set_user_info(uint64_t user_id, uint64_t player_id, uint32_t session_id) {
        user_info.user_id = user_id;
        user_info.player_id = player_id;
        user_info.session_id = session_id;
    }
};

struct message_forward : public message_head {
    uint32_t session_id;
    message_forward() {
       message_id = INNER_MSG_FORWARD;
       length = sizeof(message_forward);
       session_id = 0;
    }
};

struct message_broadcast : public message_head {
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

struct message_server_close : public message_head {
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
static void destroy_message(message_head *msg);

#endif // __MESSAGE_DEF_H__