#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>

int msgIdCounter = 0;

namespace eRPC
{
  Client::Client(std::string host, int port) : sockfd(-1), serverAddress()
  {
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr) <= 0)
    {
      throw std::runtime_error("Invalid address");
    }

    this->serverAddress = serverAddress;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      throw std::runtime_error("Failed to create socket");
    }

    if (connect(sockfd, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
      throw std::runtime_error("Failed to connect to server");
    }
  }

  Client::~Client()
  {
    Request request(msgIdCounter++, "disconnect", {});

    auto serialized = request.serialize();
    write(sockfd, serialized.c_str(), serialized.size() + 1);

    close(sockfd);
    sockfd = -1;
  }

  std::string Client::call(std::string method, std::vector<std::string> params)
  {
    Request request(msgIdCounter++, method, params);
    auto serialized = request.serialize();
    write(sockfd, serialized.c_str(), serialized.size() + 1);

    char buffer[1024] = {0};
    read(sockfd, buffer, 1024);

    Response response(buffer);

    if (!response.isOk())
    {
      throw std::runtime_error(response.getResult());
    }

    return response.getResult();
  }
}