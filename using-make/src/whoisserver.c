/**
 * @file whoisserver.c
 * @brief A whois server
 * @version 1.0
 * @date 2024-11-13
 */

#include <whois.h>

int main(void)
{

    int status, serverfd;
    struct addrinfo hints;

    // man getaddrinfo
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Set socket for server (binding)
    serverfd = setsocket(NULL, PORT, hints, SSOCK_BIND);

    // Set socket for reuse
    int optval = 1;
    if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        handle_error("setsockopt");

    // Prepare socket to await for new connections
    status = listen(serverfd, 0);
    if (status < 0)
        perror("listen");

    fprintf(stdout, "Server is listening on localhost:%s\n", PORT);

    for (;;)
    {
        // Store client addr info
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(struct sockaddr_in));
        socklen_t client_addr_len = 0;

        int clientfd = accept(serverfd, (struct sockaddr *)&client_addr,
                              &client_addr_len);

        if (clientfd < 0)
            handle_error("accept");

        // To handle multiple client-connections, each connection is allocated
        // to a new process
        pid_t pid = fork();

        if (pid == -1)
            handle_error("fork");

        // We are in child process
        if (pid == 0)
        {
            size_t total_nread = 0;
            char buffer[BUFFER_SIZE];
            memset(buffer, '\0', BUFFER_SIZE);

            if (readfrom(clientfd, buffer, &total_nread) == -1)
                handle_error("recv");

            // Set to null terminator for later execvp
            buffer[total_nread - 2] = '\0';
            buffer[total_nread - 1] = '\0';

            char command_str[1024];
            memset(command_str, '\0', 1024);
            strcpy(command_str, buffer);

            char *token = strtok(command_str, " ");

            if (strcmp(token, "whois") == 0)
            {
                char arguments[BUFFER_SIZE];
                memset(arguments, '\0', BUFFER_SIZE);

                strcpy(arguments, buffer + strlen(token) + 1);

                char *options[100];
                char *opt;
                int i = 0;

                options[i++] = token;
                opt = strtok(arguments, " ");
                while (opt != NULL)
                {
                    options[i++] = opt;
                    opt = strtok(NULL, " ");
                }
                options[i++] = (char *)0;

                if (dup2(clientfd, STDOUT_FILENO) == -1)
                    handle_error("dup2");

                if (dup2(clientfd, STDERR_FILENO) == -1)
                    handle_error("dup2");

                if (close(clientfd) == -1)
                    handle_error("close");

                if (close(serverfd) == -1)
                    handle_error("close");

                // man execvp
                execvp(COMMAND, options);

                handle_error("execvp");
            }
            else
            {
                size_t total_nsent = 0;
                char *res = "Internal error: the command is not supported!\n";

                if (writeto(clientfd, res, &total_nsent) == -1)
                    handle_error("send");

                if (close(clientfd) == -1)
                    handle_error("close");

                if (close(serverfd) == -1)
                    handle_error("close");

                exit(EXIT_SUCCESS);
            }
        }

        if (close(clientfd) == -1)
            handle_error("close");
    }

    if (close(serverfd) == -1)
        handle_error("close");

    return 0;
}
