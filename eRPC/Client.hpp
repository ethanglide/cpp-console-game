#ifndef ERPC_CLIENT_HPP
#define ERPC_CLIENT_HPP

#include <string>
#include <netinet/in.h>

namespace eRPC
{
  class Client
  {
  public:
    Client(std::string host, int port);
    ~Client();
    void openConnection();
    void closeConnection();
    void call(std::string method);
  
  private:
    int sockfd;
    sockaddr_in serv_addr;
  };
}

#endif // ERPC_CLIENT_HPP