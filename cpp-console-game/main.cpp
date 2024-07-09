#include "GameServer.hpp"
#include "GameClient.hpp"

#include <iostream>

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << "<client/server> <port> <host>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string mode = argv[1];
  int port = std::stoi(argv[2]);
  std::string host = argv[3];

  if (mode == "server")
  {
    ConsoleGame::GameServer server(port, 20, 10, "#");
  }
  else if (mode == "client")
  {
    ConsoleGame::GameClient client(host, port);
  }
  else
  {
    std::cerr << "Invalid mode" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}