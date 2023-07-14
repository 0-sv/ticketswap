cmake_minimum_required(VERSION 3.16.3)
project(ticketswap)

set(CMAKE_CXX_STANDARD 20)

find_package(LibXml2 REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

add_executable(ticketswap main.cpp)
target_link_libraries(ticketswap ${LIBXML2_LIBRARIES} cpr::cpr)
