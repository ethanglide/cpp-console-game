#ifndef ERPC_CLIENT_HPP
#define ERPC_CLIENT_HPP

#include <string>
#include <vector>
#include <netinet/in.h>

namespace eRPC
{
  class Client
  {
  public:
    Client(std::string host, int port);
    ~Client();
    std::string call(std::string method, std::vector<std::string> params);
  
  private:
    int sockfd;
    sockaddr_in serverAddress;

    void openConnection();
    void closeConnection();
  };
}

#endif // ERPC_CLIENT_HPP