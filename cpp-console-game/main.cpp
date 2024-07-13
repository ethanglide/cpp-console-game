#include "GameServer.hpp"
#include "GameClient.hpp"

#include <iostream>

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " <client/server> <port>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string mode = argv[1];
  int port = std::stoi(argv[2]);

  if (mode == "server")
  {
    ConsoleGame::GameServer server(port, 20, 10, "#");
  }
  else if (mode == "client")
  {
    if (argc < 4)
    {
      std::cerr << "Usage: " << argv[0] << " client <port> <host>" << std::endl;
      return EXIT_FAILURE;
    }

    std::string host = argv[3];

    ConsoleGame::GameClient client(host, port);
  }
  else
  {
    std::cerr << "Invalid mode \"" << mode << "\"" << std::endl;
    std::cerr << "Usage: " << argv[0] << " <client/server> <port>" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}