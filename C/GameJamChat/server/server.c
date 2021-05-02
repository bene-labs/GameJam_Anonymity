/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "../include/ftp.h"

void handle_client_request(server_info_t *server, int client_fd)
{
    char buffer[1024] = {0};
    char *valid_commands[8] = {"USER ", "PASS ", "QUIT", "NOOP", \
"PWD", "CWD ", "CDUP", "HELP"};
    void (*commands[8]) (server_info_t *server, int client_fd, char *command) \
= {&user, &password, &quit, &noop, &pwd, &cwd, &cdup, &simple_help};
    char *temp;

    read(client_fd, buffer, 1024);
    if (strlen(buffer) == 0)
        return;
    for (int i = 0; i < 1; i++) {
        if ((temp = strstr(buffer, valid_commands[i])) != NULL && \
strcmp(temp, buffer) == 0) {
            commands[i](server, client_fd, \
&buffer[strlen(valid_commands[i])]);
            return;
        }
    }
    if (strlen(buffer) != 0 && strcmp("\r\n", buffer) != 0)
        write_message_to_all_users(server, client_fd, buffer);
    //write(client_fd, "500\r\n", strlen("500\r\n"));
}

void write_message_to_all_users(server_info_t *server, int client_fd, char *message)
{
    //char *username = get_corresponding_user_info(client_fd, server->active_users).username;

    for (user_list_t *temp = server->active_users; temp; temp = temp->next) {
        if (temp->fd == client_fd)
            continue;
        /*write(temp->fd, "[", 1);
        write(temp->fd, username, strlen(username));
        write(temp->fd, "]: ", 3);*/
        write(temp->fd, message, strlen(message));
    }
}

void run_server(server_info_t server)
{
    FD_ZERO(&server.sockets);
    FD_SET(server.fd, &server.sockets);
    fd_set active_sockets;

    server.address_len = sizeof(server.address);
    server.biggest_fd = server.fd;
    server.home_dir = realpath(server.home_dir, NULL);
    server.active_users = malloc(sizeof(user_list_t));
    server.active_users->login.username = NULL;
    server.active_users->login.passwd = NULL;
    server.active_users->next = NULL;
    server.active_users->fd = -1;
    server_loop(server, active_sockets);
}