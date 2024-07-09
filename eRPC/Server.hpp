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
     * Start the server loop. This will block until the server is stopped.
     */
    void start();

    /**
     * Stop the server loop.
     */
    void stop();

    /**
     * Bind a method to a callback.
     */
    void bindMethod(std::string method, std::function<std::pair<bool, std::string>(std::vector<std::string>)> callback);

  private:
    int sockfd;
    bool running;
    std::unordered_map<std::string, std::function<std::pair<bool, std::string>(std::vector<std::string>)>> methods;

    /**
     * Keep a socket open and serve a client until they disconnect.
     */
    void serveClient(int connfd);
  };
}

#endif // ERPC_SERVER_HPP