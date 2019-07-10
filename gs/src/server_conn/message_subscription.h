#ifndef __MESSAGE_REGISTER_H__
#define __MESSAGE_REGISTER_H__ 

#include <map>
#include <vector>

#include "type_def.h"
#include "agent.h"

USING_XLOGIC
// 管理消息订阅，其他服务器会向连接服订阅消息，连接服会根据订阅的情况向对应的服务器转发消息
class message_subscription {
private:
    message_subscription();
    ~message_subscription();

public:
    static message_subscription * get_instance();
    static void destroy();

    void subscribe(uint32_t msg_id, agent * ag);

    void unsubscribe(uint32_t msg_id, agent * ag);
    void unsubscribe(uint32_t msg_id);
    void unsubscribe(agent *ag);

    void get_subscription(uint32_t msg_id, std::vector<agent *> &agents);

private:
    static message_subscription *       m_instance;
    std::multimap<uint32_t, agent *>    m_subscription;
};

#endif // __MESSAGE_REGISTER_H__
