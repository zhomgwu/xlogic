#include "inner_listener.h"
#include <netinet/in.h>

XLOGIC_BEGIN

inner_listener::inner_listener() 
: m_peer_srv_type(SERVER_TYPE_NULL)
, m_peer_srv_agent(nullptr) {

}

inner_listener::~inner_listener() {

}

void inner_listener::set_peer_srv_type(uint32_t srv_type) {
    m_peer_srv_type = srv_type;
}

void inner_listener::set_authorize_host(std::string host) {
    m_authorize_host = host;
}

bool inner_listener::check_address(struct sockaddr *sa, int socklen) {
    if (m_peer_srv_agent) {
        // 已有连接不允许新的
        return false;
    }
    if (m_authorize_host != "") {
        char coming_addr[INET_ADDRSTRLEN] = {};
        struct sockaddr_in *sai = (struct sockaddr_in *)sa;
        evutil_inet_ntop(AF_INET, &sai->sin_addr, coming_addr, sizeof(coming_addr));    
        if (m_authorize_host != coming_addr) {
            return false;
        }
    }
    return true;
}

void inner_listener::on_new_agent(agent* ag) {
    if (!m_peer_srv_agent) {
        m_peer_srv_agent = ag;
    }
}

void inner_listener::on_disconnect(agent* ag) {
    if (m_peer_srv_agent) {
        m_peer_srv_agent = nullptr;
    }
}

XLOGIC_END
