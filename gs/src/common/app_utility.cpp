#include "app_utility.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

namespace util {

bool lock_and_record_pid(std::string pid_file_name) {
    char buf[16] = {0};
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;

    int fd = open(pid_file_name.c_str(), O_CREAT | O_WRONLY, 0600);
    if (fd < 0)
        return false;
    if (fcntl(fd, F_SETLK, &lock) < 0) 
        return false;
    if (ftruncate(fd, 0) != 0)
        return false;

    sprintf(buf, "%lu", (unsigned long)getpid());
    write(fd, buf, strlen(buf));
    //不要close(fd)，否则锁会被释放
    return true;
}

}
