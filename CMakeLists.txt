cmake_minimum_required(VERSION 2.8)

PROJECT( onc_ls )

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -std=c++11")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
endif()

include_directories(.)
include_directories(src/)

FILE(GLOB_RECURSE onc_ls_SRCS

  src/*.h
  src/*.c
  )

ADD_EXECUTABLE(onc_ls ${onc_ls_SRCS})