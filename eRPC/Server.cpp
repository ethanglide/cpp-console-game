#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <unistd.h>
#include <memory>

namespace eRPC
{
  Server::Server(int port) : sockfd(-1), running(false)
  {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      throw std::runtime_error("Failed to bind socket");
    }

    if (listen(sockfd, 5) < 0)
    {
      throw std::runtime_error("Failed to listen on socket");
    }
  }

  Server::~Server()
  {
    stop();
  }

  void Server::start()
  {
    if (running)
    {
      return;
    }

    running = true;

    while (running)
    {
      auto connfd = accept(sockfd, (sockaddr *)NULL, NULL);

      char buffer[1024] = {0};
      read(connfd, buffer, 1024);
      Request request(buffer);

      std::unique_ptr<Response> response;
      if (methods.find(request.getMethod()) != methods.end())
      {
        auto method = methods[request.getMethod()];
        auto ret = method(request.getParams());

        response = std::make_unique<Response>(Response(
            request.getMsgid(),
            ret.first,
            ret.second));
      }
      else
      {
        response = std::make_unique<Response>(Response(
            request.getMsgid(),
            false,
            "Method \"" + request.getMethod() + "\" not found"));
      }

      auto serialized = response->serialize();
      write(connfd, serialized.c_str(), serialized.size() + 1);

      close(connfd);
    }

    close(sockfd);
  }

  void Server::stop()
  {
    running = false;
  }

  void Server::bindMethod(std::string method, std::function<std::pair<bool, std::string>(std::vector<std::string>)> callback)
  {
    methods[method] = callback;
  }
}