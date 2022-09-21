# CMakeList.txt : CMake project for Client-ServerModel, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Client-ServerModel "Client-ServerModel.cpp" "Client-ServerModel.h" "stdafx.h" "targetver.h" "Server.cpp" "Client.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Client-ServerModel PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

#find_package(Catch2 3 REQUIRED)

#target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)
