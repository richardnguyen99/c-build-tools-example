#include <whois.h>

int parsecmd(int argc, char *argv[], struct command_t *command)
{
    memset(command->hostname, 0, BUFFER_SIZE);
    memset(command->port, 0, BUFFER_SIZE);
    memset(command->cmd_name, 0, BUFFER_SIZE);
    memset(command->cmd_args, 0, BUFFER_SIZE);
    memset(command->cmd_object, 0, BUFFER_SIZE);
    command->cmd_objlen = 0;

    strcpy(command->cmd_name, argv[2]);

    for (int i = 3; i < argc - 1; ++i)
    {
        memset(command->cmd_args[i - 3], '\0', 50);
        strcpy(command->cmd_args[i - 3], argv[i]);
        command->cmd_objlen = i - 3;
    }
    strcpy(command->cmd_object, argv[argc - 1]); // Maybe there are some options

    char addr[BUFFER_SIZE];
    memset(addr, '\0', BUFFER_SIZE);
    strcpy(addr, argv[1]);

    struct host_t host;
    memset(&host, 0, sizeof(struct host_t));

    if (parsehost(addr, &host) == -1)
        return 1;

    strcpy(command->hostname, host.hostname);
    strcpy(command->port, host.port);

    return 0;
}

void buildcmdstr(char *buffer, struct command_t command)
{
    strcat(buffer, command.cmd_name);
    strcat(buffer, " ");

    for (size_t i = 0; i < command.cmd_objlen; ++i)
    {
        strcat(buffer, command.cmd_args[i]);
        strcat(buffer, " ");
    }

    strcat(buffer, command.cmd_object);
    strcat(buffer, "\r\n");
}

int parsehost(char *addr, struct host_t *host)
{
    char *token = strtok(addr, ":");

    if (token == NULL)
    {
        fprintf(stderr, "Invalid hostname syntax\n");
        exit(EXIT_FAILURE);
    }

    host->hostname = token;

    token = strtok(NULL, ":");
    if (token == NULL)
    {
        fprintf(stderr, "Invalid hostname syntax\n");
        exit(EXIT_FAILURE);
    }

    char *end;
    strtod(token, &end);
    if (*end != '\0')
    {
        fprintf(stderr, "Port number must be a number\n");
        exit(EXIT_FAILURE);
    }

    host->port = token;

    return 0;
}

int __isendofmessage(const char *buffer, size_t len)
{
    return len >= 2 && buffer[len - 2] == '\r' && buffer[len - 1] == '\n';
}

int readfrom(int sockfd, char *buffer, size_t *len)
{
    ssize_t nread = 0;

    // Return a blocking event to capture all the message sent from `sockfd`.
    for (;;)
    {
        nread = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (nread == -1)
            return -1;

        *len += (size_t)nread;

        if (__isendofmessage(buffer, *len))
            break;
    }

    return 0;
}

int writeto(int sockfd, char *buffer, size_t *total)
{
    ssize_t nsent = 0;
    size_t len = strlen(buffer);

    while (*total < len)
    {
        nsent = send(sockfd, buffer + *total,
                     len - *total, 0);

        if (nsent == -1 || nsent == 0)
            return -1;

        *total += (size_t)nsent;
    }

    return 0;
}

int setsocket(const char *host, const char *port, struct addrinfo hints, int flags)
{
    int sockfd, status;
    struct addrinfo *results, *rp;

    if ((status = getaddrinfo(host, port, &hints, &results)) != 0)
    {
        // perror doesn't give a full detail on the error
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (rp = results; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        // In case socket failed, there might still some left
        if (sockfd == -1)
            continue;

        // Failed to bind the socket to the local address

        if (flags == 0)
            status = bind(sockfd, rp->ai_addr, rp->ai_addrlen);
        else
            status = connect(sockfd, rp->ai_addr, rp->ai_addrlen);

        if (status != 0)
        {
            if (close(sockfd) == -1)
                handle_error("close");
            continue;
        }

        break; // Success
    }

    freeaddrinfo(results);

    if (rp == NULL)
    {
        fprintf(stderr, "No available host\n");
        exit(EXIT_FAILURE);
    }

    if (status != 0)
        handle_error("connect");

    return sockfd;
}
