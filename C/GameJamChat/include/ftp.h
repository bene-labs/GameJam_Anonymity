/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#ifndef FTP_FTP_H
#define FTP_FTP_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <dirent.h>

typedef struct user_info {
    char *username;
    char *passwd;
    char *working_dir;
} user_info_t;

typedef struct user_list {
    user_info_t login;
    int fd;
    struct user_list *next;
} user_list_t;


typedef struct server_info {
    int server_port;
    struct sockaddr_in address;
    int fd;
    fd_set sockets;
    int biggest_fd;
    int address_len;
    char *home_dir;
    user_list_t *active_users;
} server_info_t;

void error_exit(char *message);
int display_usage(void);
void handle_client_request(server_info_t *server, int client_fd);
void run_server(server_info_t server);
int server_loop(server_info_t server, fd_set active_sockets);
void user(server_info_t *server, int client_fd, char *command);
void password(server_info_t *server, int client_fd, char *command);
void quit(server_info_t *server, int client_fd, char *command);
void noop(server_info_t *server, int client_fd, char *command);
void pwd(server_info_t *server, int client_fd, char *command);
void cwd(server_info_t *server, int client_fd, char *command);
void cdup(server_info_t *server, int client_fd, char *command);
void simple_help(server_info_t *server, int client_fd, char *command);
user_info_t get_corresponding_user_info(int client_fd, user_list_t *users);
int is_user_logged_in(int client_fd, user_list_t *users);
int set_corresponding_user_name(int client_fd, char *username, \
user_list_t *users);
int set_corresponding_password(int client_fd, char *password, \
user_list_t *users);
int set_corresponding_dir(int client_fd, char *path, \
user_list_t *users);
void add_new_active_user(server_info_t *server, int new_client_fd);
int remove_corresponding_user(int client_fd, user_list_t *users);
void write_message_to_all_users(server_info_t *server, int client_fd, char *message);

#endif //FTP_FTP_H