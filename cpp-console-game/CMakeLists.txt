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

add_executable(
  cpp-console-game
  main.cpp
  )

target_link_libraries(
  cpp-console-game PRIVATE
  GameState
  conio
  eRPC
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