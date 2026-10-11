cmake_minimum_required(VERSION 3.20)

add_library(blafPch INTERFACE)

target_precompile_headers(blafPch INTERFACE blafPch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)