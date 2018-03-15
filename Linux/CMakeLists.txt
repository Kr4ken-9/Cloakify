cmake_minimum_required(VERSION 3.9)
project(Cloakify)

set(CMAKE_CXX_STANDARD 11)

add_library(Cloakify SHARED Cloakify.cpp Cloakify.h base64.h base64.cpp)