#ifndef __MESSAGE_PROCESSOR_H__
#define __MESSAGE_PROCESSOR_H__

#include <type_traits>
#include "noncopyable.h"

namespace xlogic {

class message_processor : public noncopyable {
public:
    message_processor();
    ~message_processor();

public:

    void *raw_data();

    uint32_t size();

    uint32_t length();

    void append(void *data, uint32_t len);

    bool get_data(void *dst, uint32_t len);
    // 该方法用于解析POD数据类型，非POD不允许使用
    template<typename T>
    T * try_parse() {
        if (!std::is_trivial<T>::value) {
            return nullptr;
        }
        if (m_length < sizeof(T)) {
            return nullptr;
        }
        return (T *)(m_data);
    }

private:

    bool check_size(uint32_t size);

private:
    void *          m_data;
    uint32_t        m_length;
    uint32_t        m_size;
};

}

#endif // __MESSAGE_PROCESSOR_H__