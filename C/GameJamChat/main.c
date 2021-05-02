/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "include/ftp.h"
#include <signal.h>

void sigpipe_handler(int unused)
{
    exit(84);
}

void error_exit(char *message)
{
    fprintf(stderr, "Error: %s", message);
    exit(84);
}

int display_usage(void)
{
    printf("USAGE: ./myftp port home_dir\n" \
"\t\tport is the port number on which the server socket listens\n" \
"\t\thome_dir is the home_dir to the home directory for the Anonymous user)\n");
    return 84;
}

server_info_t create_server(int argc, char **argv)
{
    server_info_t res;
    int opt = 1;

    if (argc != 3 || !atoi(argv[1]))
        exit(display_usage());
    if (!(res.fd = socket(AF_INET, SOCK_STREAM, 0)))
        error_exit("cannot create server socket\n");
    res.server_port = atoi(argv[1]);
    res.home_dir = argv[2];
    res. address.sin_family = AF_INET;
    res.address.sin_addr.s_addr = INADDR_ANY;
    res.address.sin_port = htons(res.server_port);
    if (setsockopt(res.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, \
&opt, sizeof(opt)))
        error_exit("cannot set sockopt to make it reusable\n");
    return res;
}

int main(int argc, char **argv)
{
    server_info_t server;
    DIR *dp;

    server = create_server(argc, argv);
    if (bind(server.fd, (struct sockaddr *) &server.address, \
sizeof(server.address)) < 0)
        error_exit("bind failed");
    if (listen(server.fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if (!(dp = opendir(server.home_dir)))
        error_exit("Invalid Path: Cannot open Directory.\n");
    sigaction(SIGPIPE, &(struct sigaction){sigpipe_handler}, NULL);
    run_server(server);
    return 0;
}