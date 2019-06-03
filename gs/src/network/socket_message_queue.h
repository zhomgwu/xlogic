#ifndef __SOCKET_MESSAGE_QUEUE_H__
#define __SOCKET_MESSAGE_QUEUE_H__

#include <queue>

namespace xlogic {

struct socket_message {
    void *data;
    uint32_t length;
};

// 消息队列，主要是对消息统一存放，方便支持多线程
class socket_message_queue {
public:
    socket_message_queue();
    ~socket_message_queue();

public:

    static socket_message_queue *get_instance();
    static void destroy();

    static socket_message * new_socket_message(void *data, uint32_t length);
    static void delete_socket_message(socket_message * msg);

    void push(socket_message * msg);

    socket_message * pop();

    std::queue<socket_message *> & get_messages();

    uint32_t message_count();

private:

    static socket_message_queue *m_instance;
    std::queue<socket_message *>  m_messages;
};

}
#endif //__SOCKET_MESSAGE_QUEUE_H__
