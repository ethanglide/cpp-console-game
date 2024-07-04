add_library(
  conio
  conio.hpp
  conio.cpp
  )

target_include_directories(
  conio
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )