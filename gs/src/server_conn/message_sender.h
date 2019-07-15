#ifndef __MESSAGE_SENDER_H__
#define __MESSAGE_SENDER_H__

#include <vector>

class message_sender {
public:
    static bool send_to_db(void *data, int len);
    static bool send_to_client(void *data, int len);
    static bool broadcast(std::vector<uint32_t> &sessions, void *data, int len);
};

#endif //__MESSAGE_SENDER_H__

