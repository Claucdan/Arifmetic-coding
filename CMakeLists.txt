cmake_minimum_required(VERSION 3.0.0)
project(first VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

INCLUDE_DIRECTORIES(
    C:/Стол/vcpkg/installed/x64-windows/include
)
  
LINK_DIRECTORIES(
    C:/Стол/vcpkg/installed/x64-windows/lib
)

add_executable(first main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
TARGET_LINK_LIBRARIES(first
  gmp
)