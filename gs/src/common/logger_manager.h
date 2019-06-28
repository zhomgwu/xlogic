#ifndef __LOGER_MANAGER_H__
#define __LOGER_MANAGER_H__

#include <string>
#include "log4z.h"

class logger_manager {
private:
    logger_manager();
    ~logger_manager();

public:    
    static logger_manager * get_instance();    
    void init_log(std::string path);
    void start_log();
    void stop_log();

    LoggerId get_info_logger();
    LoggerId get_debug_logger();
    LoggerId get_error_logger();
    LoggerId get_fatal_logger();
    LoggerId get_warn_logger();
    
private:
    LoggerId m_info_logger;
    LoggerId m_debug_logger;
    LoggerId m_error_logger;
    LoggerId m_fatal_logger;
    LoggerId m_warn_logger;
    std::string m_log_path;
};

#if defined(DEBUG) || defined(Debug)
#define LOGDEBUG(...)  LOGFMT_DEBUG(logger_manager::get_instance()->get_debug_logger(), ##__VA_ARGS__)
#else
#define LOGDEBUG(...) 
#endif
#define LOGINFO(...)   LOGFMT_INFO(logger_manager::get_instance()->get_info_logger(), ##__VA_ARGS__)
#define LOGERROR(...)  LOGFMT_ERROR(logger_manager::get_instance()->get_error_logger(), ##__VA_ARGS__)
#define LOGFATAL(...)  LOGFMT_FATAL(logger_manager::get_instance()->get_fatal_logger(), ##__VA_ARGS__)
#define LOGWARN(...)   LOGFMT_WARN(logger_manager::get_instance()->get_warn_logger(), ##__VA_ARGS__)

#endif //__LOGER_MANAGER_H__