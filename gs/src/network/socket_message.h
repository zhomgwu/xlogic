#ifndef __SOCKET_MESSAGE_H__
#define __SOCKET_MESSAGE_H__

namespace xlogic {

class socket_message : public noncopyable {
public:
    socket_message();
    ~socket_message();

public:

    void *raw_data();

    uint32_t size();

    uint32_t length();

    void append(void *data, uint32_t len);

    bool get_data(void *dst, uint32_t len);

    template<typename T>
    T * try_parse();

private:

    bool check_size(uint32_t size);

private:
    void *          m_data;
    uint32_t        m_length;
    uint32_t        m_size;
};

}

#endif // __SOCKET_MESSAGE_H__