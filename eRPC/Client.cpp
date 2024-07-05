#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

namespace eRPC
{
  Client::Client(std::string host, int port) : sockfd(-1), serv_addr()
  {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0)
    {
      throw std::runtime_error("Invalid address");
    }

    this->serv_addr = serv_addr;
  }

  Client::~Client()
  {
    closeConnection();
  }

  void Client::openConnection()
  {
    if (sockfd < 0)
    {
      throw std::runtime_error("Socket not created");
    }

    if (connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      throw std::runtime_error("Failed to connect to server");
    }

    std::cout << "Connected to server" << std::endl;
  }

  void Client::closeConnection()
  {
    close(sockfd);
  }

  void Client::call(std::string method)
  {
    if (sockfd < 0)
    {
      throw std::runtime_error("Socket not created");
    }

    Request request(0, method, {"First argument", "Another argument"});
    auto serialized = request.serialize();
    write(sockfd, serialized.c_str(), serialized.size() + 1);

    char buffer[1024] = {0};
    read(sockfd, buffer, 1024);

    Response response(buffer);
    std::cout << "Received response:\n" << response.serialize() << std::endl;
  }
}