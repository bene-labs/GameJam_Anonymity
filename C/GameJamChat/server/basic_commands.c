/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "../include/ftp.h"

void user(server_info_t *server, int client_fd, char *command)
{
    const char *response_success =  "230\r\n";
    const char *response_missing_passwort = "331\r\n";
    const char *response_failure = "530\r\n";

    if (command != NULL && strcmp("\r\n", command) != 0) {
        if (!get_corresponding_user_info( \
client_fd, server->active_users).passwd)
            write(client_fd, response_missing_passwort, \
strlen(response_missing_passwort));
        else
            write(client_fd, response_success, strlen(response_success));
        set_corresponding_user_name( \
client_fd, command, server->active_users);
    } else
        write(client_fd, response_failure, strlen\
(response_failure));
}

void password(server_info_t *server, int client_fd, char *command)
{
    const char *response_success =  "230\r\n";
    const char *response_no_user = "332\r\n";
    const char *response_failure = "530\r\n";

    if (command != NULL && strcmp("\r\n", command) == 0) {
        if (!get_corresponding_user_info( \
client_fd, server->active_users).username)
            write(client_fd, response_no_user, strlen(response_no_user));
        else {
            write(client_fd, response_success, strlen(response_success));
            set_corresponding_password(client_fd, "", server->active_users);
        }
    } else
        write(client_fd, response_failure, strlen(response_failure));
}

void quit(server_info_t *server, int client_fd, char *command)
{
    const char *response_success =  "221\r\n";
    const char *response_failure = "500\r\n";

    if (command != NULL && strcmp("\r\n", command) == 0) {
        write(client_fd, response_success, strlen(response_success));
        remove_corresponding_user(client_fd, server->active_users);
        close(client_fd);
        FD_CLR(client_fd, &server->sockets);
    }
    else
        write(client_fd, response_failure, strlen(response_failure));
}

void noop(server_info_t *server, int client_fd, char *command)
{
    const char *response_success =  "200\r\n";
    const char *response_failure = "500\r\n";

    if (!is_user_logged_in(client_fd, server->active_users)) {
        write(client_fd, "503\r\n", 5);
        return;
    }
    if (command != NULL && strcmp("\r\n", command) == 0) {
        write(client_fd, response_success, strlen(response_success));
    }
    else
        write(client_fd, response_failure, strlen(response_failure));
}

void simple_help(server_info_t *server, int client_fd, char *command)
{
    const char *help = "USER PASS CWD CDUP QUIT DELE PWD PASV" \
"PORT HELP NOOP RETR STOR LIST";

    if (command != NULL && strcmp("\r\n", command) == 0) {
        write(client_fd, "214 ", 4);
        write(client_fd, help, strlen(help));
        write(client_fd, "\r\n", 2);
    }
    else
        write(client_fd, "500\r\n", 5);
}