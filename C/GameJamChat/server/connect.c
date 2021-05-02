/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "../include/ftp.h"

void connect_new_client_socket(server_info_t *server)
{
    int new_client;

    if ((new_client = accept(server->fd, (struct sockaddr *)&server->address, \
(socklen_t *)&server->address_len)) < 0) {
        perror("accept failed.");
        exit(84);
    }
    printf("Connection from %s:%d\n", \
inet_ntoa(server->address.sin_addr), \
ntohs(server->address.sin_port));
    write(new_client, "Successfully Connected\n", strlen("Successfully Connected\n"));
    FD_SET(new_client, &server->sockets);
    if (new_client > server->biggest_fd)
        server->biggest_fd = new_client;
    add_new_active_user(server, new_client);
}

void handle_socket_input(server_info_t *server, int i)
{
    if (i == server->fd)
        connect_new_client_socket(server);
    else
        handle_client_request(server, i);
}

int server_loop(server_info_t server, fd_set active_sockets)
{
    fd_set stdin_set;
    FD_ZERO(&stdin_set);
    FD_SET(0, &stdin_set);

    while (1) {
        active_sockets = server.sockets;
        if (select(FD_SETSIZE, &active_sockets, &stdin_set, NULL, NULL) < 0) {
            error_exit("select failed.\n");
        }
        for (int i = 0; i <= server.biggest_fd; i++) {
            if (FD_ISSET(i, &active_sockets)) {
                handle_socket_input(&server, i);
            }
        }
    }
}