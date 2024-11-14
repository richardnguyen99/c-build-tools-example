/**
 * @file whoisclient.c
 * @brief A whois client
 * @version 1.0
 * @date 2024-11-13
 */

#include <whois.h>

int main(int argc, const char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: \
whoisclient hostname:server_port whois [option] argument-list\n");
        exit(1);
    }

    int sockfd;
    struct command_t command;
    struct addrinfo hints;

    memset(&command, 0, sizeof(struct command_t));
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    // Initialize command struct to construct a request message.
    memset(command.hostname, 0, BUFFER_SIZE);
    memset(command.port, 0, BUFFER_SIZE);
    memset(command.cmd_name, 0, BUFFER_SIZE);
    memset(command.cmd_args, 0, 10 * 50); // 10 elements with 50 char max.
    memset(command.cmd_object, 0, BUFFER_SIZE);
    command.cmd_objlen = 0;

    // Parse arguments to command struct
    strcpy(command.cmd_name, argv[2]);
    for (int i = 3; i < argc - 1; ++i)
    {
        memset(command.cmd_args[i - 3], '\0', 50);
        strcpy(command.cmd_args[i - 3], argv[i]);
        command.cmd_objlen++;
    }
    strcpy(command.cmd_object, argv[argc - 1]); // Maybe there are some options

    // Parse address string hostname:port to host struct
    char addr[BUFFER_SIZE];
    memset(addr, '\0', BUFFER_SIZE);
    strcpy(addr, argv[1]);

    struct host_t host;
    memset(&host, 0, sizeof(struct host_t));

    if (parsehost(addr, &host) == -1)
        return -1;

    strcpy(command.hostname, host.hostname);
    strcpy(command.port, host.port);

    // Configure socket file descriptor.
    sockfd = setsocket(command.hostname, command.port,
                       hints, SSOCK_CONNECT);

    char msg[BUFFER_SIZE];
    memset(msg, '\0', BUFFER_SIZE);

    // Build the command message that will be sent to the server
    buildcmdstr(msg, command);

    size_t total_nsent = 0;

    // Send command message to server
    if (writeto(sockfd, msg, &total_nsent) < 0)
        handle_error("send");

    char res[BUFFER_SIZE];
    memset(res, '\0', BUFFER_SIZE);

    ssize_t nrecv = 0;
    size_t total_nrecv = 0;

    // Receive response from the server
    while ((nrecv = recv(sockfd, res, BUFFER_SIZE, 0)) > 0)
    {
        // Write the response to stdout
        ssize_t nwrte = write(STDOUT_FILENO, res, nrecv);

        if (nwrte == -1)
            handle_error("write");

        total_nrecv += (size_t)nrecv;
    }

    if (nrecv == -1)
        handle_error("recv");

    if (close(sockfd) != 0)
        handle_error("close");

    return 0;
}
