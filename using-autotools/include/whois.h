/**
 * @file whois.h
 * @brief A Whois Header
 * @version 1.0
 * @date 2024-11-13
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#ifndef __WHOIS_H
#define __WHOIS_H 1

// IO & STD libs
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linux standards
#include <unistd.h>

// Socket programming
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT "10496"
#define COMMAND "/usr/bin/whois"
#define BUFFER_SIZE 4096

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

#define SSOCK_BIND 0
#define SSOCK_CONNECT 1

/* A simple struct that stores info about a host */
struct host_t {
  char *hostname;
  char *port;
};

/* A simple struct that stores the command message */
struct command_t {
  char hostname[BUFFER_SIZE];
  char port[BUFFER_SIZE];
  char cmd_name[BUFFER_SIZE];
  char cmd_object[BUFFER_SIZE];
  char cmd_args[10][50];

  size_t cmd_objlen;
};

/**
 * @brief Take and parse the command line arguments.
 *
 * The CLI supposes the following format:
 *
 * ```
 * whoisclient hostname:server_port whois [option] argument-list
 * ```
 *
 * @param argc Argument count from the CLI
 * @param argv List of arugments from the CLI
 * @param command Buffer to store the parsed command
 *
 * @return int On success, it returns 0. On error, it returns -1.
 */
int parsecmd(int argc, char *argv[], struct command_t *command);

/**
 * @brief Build a command string from a `command_t` struct.
 *
 * @param buffer Buffer to store the command string
 * @param command `command_t` struct
 */
void buildcmdstr(char *buffer, struct command_t command);

/**
 * @brief Parse an `addr` string to struct `host`.
 *
 * @param addr Address string
 * @param host `host_t` struct
 * @return On success, it returns 0. On error, it returns -1.
 */
int parsehost(char *addr, struct host_t *host);

/**
 * @brief Set up a socket connection.
 *
 * @param host Hostname
 * @param port Port number
 * @param hints `addrinfo` struct
 * @param flags Flags for binding or connecting
 * @return On success, it returns a socket file descriptor. On error, it returns
 * -1.
 */
int setsocket(const char *host, const char *port, struct addrinfo hints,
              int flags);

/**
 * @brief Read and store message from socket.
 *
 * @param sockfd Socket file descriptor
 * @param buffer Storage for received message
 * @param len    Length (in bytes) for stored message
 * @return On success, it returns 0. On, error, it returns -1.
 */
int readfrom(int sockfd, char *buffer, size_t *len);

/**
 * @brief Write and send message to socket.
 *
 * @param sockfd Socket file descriptor
 * @param buffer Message to send
 * @param len    Length (in bytes) for message
 * @return On success, it returns 0. On, error, it returns -1.
 */
int writeto(int sockfd, char *buffer, size_t *len);

#endif // __WHOIS_H
