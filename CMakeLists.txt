cmake_minimum_required(VERSION 3.21)
project(True_project_7)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR C:/Mingw/include/)
set(Boost_LIBRARY_DIR C:/Mingw/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


add_executable(client client.cpp)
add_executable(server server.cpp)


target_link_libraries(client ws2_32)
target_link_libraries(server ws2_32)
