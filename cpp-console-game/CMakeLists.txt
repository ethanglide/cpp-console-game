add_library(
  Board
  Board.hpp
  Board.cpp
  )

add_library(
  GameState
  GameState.hpp
  GameState.cpp
  )

add_library(
  Player
  Player.hpp
  Player.cpp
  )

add_library(
  GameServer
  GameServer.hpp
  GameServer.cpp
  )

add_library(
  GameClient
  GameClient.hpp
  GameClient.cpp
  )

add_executable(
  cpp-console-game
  main.cpp
  )

target_link_libraries(
  GameState PRIVATE
  Board
  Player
  RandomUtils
  )

target_link_libraries(
  Player PRIVATE
  RandomUtils
  )

target_link_libraries(
  GameServer PRIVATE
  GameState
  eRPC
  )

target_link_libraries(
  GameClient PRIVATE
  eRPC
  conio
  )

target_link_libraries(
  cpp-console-game PRIVATE
  GameServer
  GameClient
  eRPC
  )