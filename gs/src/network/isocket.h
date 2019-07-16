#ifndef __ISOCKET_H__
#define __ISOCKET_H__

class isocket {
public:
    virtual void close() = 0;
    virtual bool send(void *data, int length) = 0;
};

#endif //__ISOCKET_H__
