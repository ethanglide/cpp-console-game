add_library(
  RandomUtils
  RandomUtils.hpp
  RandomUtils.cpp
  )

target_include_directories(
  RandomUtils
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )