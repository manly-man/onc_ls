cmake_minimum_required(VERSION 2.8)

project( onc_ls )

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -g -std=c++11")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -lm -g -std=c++11")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -lm -std=c++11")
endif()

include_directories(.)
include_directories(src/)

file(GLOB_RECURSE onc_ls_SRCS

  src/*.h
  src/*.c
  )

add_executable(onc_ls ${onc_ls_SRCS})

if(UNIX)
  target_link_libraries(onc_ls m)
endif(UNIX)