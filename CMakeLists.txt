cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)

project(TODO VERSION 0.1.0 LANGUAGES C CXX)

find_package(wxWidgets CONFIG REQUIRED)

add_executable(TODO WIN32 App.cpp mainFrame.cpp Task.cpp)

target_link_libraries(TODO PRIVATE wx::core wx::base)