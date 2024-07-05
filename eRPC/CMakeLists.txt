add_library(
  eRPC
  Client.hpp
  Client.cpp
  Server.hpp
  Server.cpp
  )

add_library(
  eRPC_helpers
  Request.hpp
  Request.cpp
  Response.hpp
  Response.cpp
  )

target_link_libraries(
  eRPC PRIVATE
  eRPC_helpers
  )

target_include_directories(
  eRPC
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )