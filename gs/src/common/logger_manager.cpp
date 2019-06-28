#include "logger_manager.h"

using namespace zsummer;
using namespace log4z;

logger_manager::logger_manager() {
    // 初始化为默认
    m_info_logger = LOG4Z_MAIN_LOGGER_ID;
    m_debug_logger = LOG4Z_MAIN_LOGGER_ID;
    m_error_logger = LOG4Z_MAIN_LOGGER_ID;
    m_fatal_logger = LOG4Z_MAIN_LOGGER_ID;
    m_warn_logger = LOG4Z_MAIN_LOGGER_ID;
}

logger_manager::~logger_manager() {
}

logger_manager * logger_manager::get_instance() {
    static logger_manager m;
    return &m;
}

void logger_manager::init_log(std::string path) {
    m_info_logger = ILog4zManager::getRef().createLogger("info");
    m_debug_logger = ILog4zManager::getRef().createLogger("debug");
    m_error_logger = ILog4zManager::getRef().createLogger("error");
    m_fatal_logger = ILog4zManager::getRef().createLogger("fatal");
    m_warn_logger = ILog4zManager::getRef().createLogger("warn");
    if (!path.empty()) {
        ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, path.c_str());
        ILog4zManager::getRef().setLoggerPath(m_info_logger, path.c_str());
        ILog4zManager::getRef().setLoggerPath(m_debug_logger, path.c_str());
        ILog4zManager::getRef().setLoggerPath(m_error_logger, path.c_str());
        ILog4zManager::getRef().setLoggerPath(m_fatal_logger, path.c_str());
        ILog4zManager::getRef().setLoggerPath(m_warn_logger, path.c_str());
        m_log_path = path;
    }
    // 取消控制台输出
    ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, false);
    ILog4zManager::getRef().setLoggerDisplay(m_info_logger, false);
    ILog4zManager::getRef().setLoggerDisplay(m_debug_logger, false);
    ILog4zManager::getRef().setLoggerDisplay(m_error_logger, false);
    ILog4zManager::getRef().setLoggerDisplay(m_fatal_logger, false);
    ILog4zManager::getRef().setLoggerDisplay(m_warn_logger, false);
}

void logger_manager::start_log() {
    ILog4zManager::getRef().start();
}

void logger_manager::stop_log() {
    ILog4zManager::getRef().stop();
}

LoggerId logger_manager::get_info_logger(){
    return m_info_logger;
}

LoggerId logger_manager::get_debug_logger() {
    return m_debug_logger;
}

LoggerId logger_manager::get_error_logger() {
    return m_error_logger;
}

LoggerId logger_manager::get_fatal_logger() {
    return m_fatal_logger;
}

LoggerId logger_manager::get_warn_logger() {
    return m_warn_logger;
}
