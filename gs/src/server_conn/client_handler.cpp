#include "client_handler.h"

#include <vector>
#include "client_agent.h"
#include "message_subscription.h"
#include "server_message.h"

bool client_handler::check_address(struct sockaddr *sa, int socklen) {
    return true;
}

void client_handler::on_new_agent(agent* ag) {

}

void client_handler::on_disconnect(agent* ag) {

}

void client_handler::on_message(agent* ag, void *data, int len) {
    // 来自客户端的消息，解析，根据id分配到订阅的服务器去
    client_agent * cli_ag = (client_agent*)ag;   
    message_head* head = (message_head*)data;
   
    ///////////////////////////// test 
    // echo
    ag->send(data, len);
    
    ///////////////////////////// test 
    
    // std::vector<agent *> srv_ags;
    // message_subscription::get_instance()->get_subscription(head->message_id, srv_ags);
    // for (auto &it : srv_ags) {
    //     it->send(data, len);
    // }
}

