#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__

#include <stdint.h>

#ifndef XLOGIC_BEGIN
#define XLOGIC_BEGIN namespace xlogic {
#endif 

#ifndef XLOGIC_END
#define XLOGIC_END }
#endif 

#ifndef USING_XLOGIC
#define USING_XLOGIC using namespace xlogic;
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) { \
    if ((ptr) != nullptr ) { \
        delete (ptr); \
        (ptr) = nullptr; } \
    }
#endif

#endif //__TYPE_DEF_H__
