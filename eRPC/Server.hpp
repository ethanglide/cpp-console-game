#ifndef ERPC_SERVER_HPP
#define ERPC_SERVER_HPP

#include <string>
#include <functional>
#include <unordered_map>

namespace eRPC
{
  class Server
  {
  public:
    /**
     * Construct a server on the given port.
     */
    Server(int port);

    /**
     * Destroy the server.
     */
    ~Server();

    /**
     * Start the server loop.
     */
    void start();

    /**
     * Stop the server loop.
     */
    void stop();

    /**
     * Bind a method to a callback.
     */
    void bindMethod(std::string method, std::function<void *()> callback);
  
  private:
    int sockfd;
    bool running;
    std::unordered_map<std::string, std::function<void *()>> methods;
  };
}

#endif // ERPC_SERVER_HPP