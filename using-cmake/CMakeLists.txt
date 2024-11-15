cmake_minimum_required(VERSION 3.13) 
project(using-cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set common compiler flags
set(CMAKE_C_FLAGS "-Wall -Werror")

# Check for header files
include(CheckIncludeFile)
check_include_file(fcntl.h HAVE_FCNTL_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_file(netinet/in.h HAVE_NETINET_IN_H)
check_include_file(arpa/inet.h HAVE_ARPA_INET_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(stdio.h HAVE_STDIO_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(errno.h HAVE_ERRNO_H)
check_include_file(signal.h HAVE_SIGNAL_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(time.h HAVE_TIME_H)

# Check for functions
include(CheckFunctionExists)
check_function_exists(fcntl HAVE_FCNTL)
check_function_exists(socket HAVE_SOCKET)
check_function_exists(bind HAVE_BIND)
check_function_exists(listen HAVE_LISTEN)
check_function_exists(accept HAVE_ACCEPT)
check_function_exists(close HAVE_CLOSE)
check_function_exists(read HAVE_READ)
check_function_exists(write HAVE_WRITE)
check_function_exists(recv HAVE_RECV)

# Check for declarations
include(CheckSymbolExists)
check_symbol_exists(NULL "stddef.h" HAVE_NULLPTR)

# Check for type definitions
include(CheckTypeSize)
check_type_size(pthread_t HAVE_PTHREAD_T)
check_type_size(int8_t HAVE_INT8_T)
check_type_size(ssize_t HAVE_SSIZE_T)
check_type_size(size_t HAVE_SIZE_T)
check_type_size(u_char HAVE_U_CHAR)

# Add subdirectories
add_subdirectory(src)

