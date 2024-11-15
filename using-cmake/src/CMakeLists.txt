cmake_minimum_required(VERSION 3.13) 
project(using-cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compiler flags based on the build type
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG -g -O0")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -O3")
endif()

# Compile shared library
set(BUILD_SHARED_LIBS ON)

# Add source code to library
add_library(whois whois.c ${CMAKE_SOURCE_DIR}/include/whois.h)
target_include_directories(whois PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Compile target whoisclient
add_executable(whoisclient whoisclient.c)

# Link whoisclient with whois library
target_include_directories(whoisclient PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(whoisclient whois)

# Compile target whoisserver
add_executable(whoisserver whoisserver.c)

# Link whoisserver with whois library
target_include_directories(whoisserver PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(whoisserver whois)

