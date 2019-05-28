#ifndef __WORK_DISPATCH_H__
#ifndef __WORK_DISPATCH_H__

class dispatch_rule {
public:
    bool is_legal(void *data, int len) = 0;
    int get_offset() = 0;
};

typedef std::function<(void *data, int len, user_info *usr_info)> handle_func;

class work_dispatcher {
public:

    bool new_service(uint32_t cmd, handle_func func);
    bool remove_service(uint32_t cmd);
    void dispatch(void *data, int len);

private:
    dispatch_rule * m_rule;
    std::map<uint32_t, handle_func> m_handler;
};

#endif // __WORK_DISPATCH_H__
