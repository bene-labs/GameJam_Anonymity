/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "../include/ftp.h"

void pwd(server_info_t *server, int client_fd, char *command)
{
    char *buffer = NULL;
    const char *response_success = "257\r\n";
    const char *response_failure = "500\r\n";

    if (command != NULL && strcmp("\r\n", command) == 0) {
        write(client_fd, "257 ", 4);
        write(client_fd, get_corresponding_user_info(client_fd, \
server->active_users).working_dir, strlen(get_corresponding_user_info( \
client_fd, server->active_users).working_dir));
        write(client_fd, "\r\n", 2);
    }
    else
        write(client_fd, response_failure, strlen(response_failure));
}

void cwd(server_info_t *server, int client_fd, char *command)
{
    char *buffer = NULL;
    const char *response_success = "250\r\n";
    const char *response_invalid_path = \
"550\r\n";
    const char *response_invalid_command = "500\r\n";
    DIR *dp;

    if (!is_user_logged_in(client_fd, server->active_users)) {
        write(client_fd, "503\r\n", 5);
        return;
    }
    if ((dp = opendir(strtok(command, "\r\n"))) != NULL \
&& strtok(NULL, "\r\n") == NULL) {
        set_corresponding_dir(client_fd, realpath(strtok(command, "\r\n"), \
NULL), server->active_users);
        write(client_fd, response_success, strlen(response_success));
    } else
        write(client_fd, response_invalid_path, strlen \
(response_invalid_path));
}

void cdup(server_info_t *server, int client_fd, char *command)
{
    const char *response_success = "200\r\n";
    const char *response_invalid_path = \
"550\r\n";
    char *working_dir = get_corresponding_user_info(client_fd, \
server->active_users).working_dir;
    char parent_dir[strlen(working_dir) + 2];

    if (!is_user_logged_in(client_fd, server->active_users)) {
        write(client_fd, "503\r\n", 5);
        return;
    }
    sprintf(parent_dir, "%s/..", working_dir);
    if (command != NULL && strcmp("\r\n", command) == 0 && \
(opendir(parent_dir)) != NULL) {
        set_corresponding_dir(client_fd, realpath(parent_dir, NULL), \
server->active_users);
        write(client_fd, response_success, strlen(response_success));
    } else
        write(client_fd, response_invalid_path, strlen \
(response_invalid_path));
}