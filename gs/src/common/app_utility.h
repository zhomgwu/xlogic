#ifndef __APP_UTILITY_H__
#define __APP_UTILITY_H__

#include <string>

namespace util {

// 创建pid文件
bool lock_and_record_pid(std::string pid_file_name);

}

#endif //__APP_UTILITY_H__
