cmake_minimum_required(VERSION 3.16)
project(IMS_project_2020)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMS_project_2020 ims.cpp Tank.cpp Tank.h Stats.cpp Stats.h Irrigation.cpp Irrigation.h WaterSupply.cpp WaterSupply.h Weather.cpp Weather.h)