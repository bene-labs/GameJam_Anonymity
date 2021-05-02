/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "include/ftp.h"

user_info_t get_corresponding_user_info(int client_fd, user_list_t *users)
{
    user_info_t empty_info;

    for (user_list_t *temp = users->next; temp; temp = temp->next) {
        if (temp->fd == client_fd) {
            return temp->login;
        }
    }
    empty_info.passwd = NULL;
    empty_info.username = NULL;
    return empty_info;
}

int set_corresponding_user_name(int client_fd, char *username, \
user_list_t *users)
{
    for (user_list_t *temp = users->next; temp; temp = temp->next) {
        if (temp->fd == client_fd) {
            temp->login.username = username;
            return 1;
        }
    }
    return 0;
}

int set_corresponding_password(int client_fd, char *password, \
user_list_t *users)
{
    for (user_list_t *temp = users->next; temp; temp = temp->next) {
        if (temp->fd == client_fd) {
            temp->login.passwd = password;
            return 1;
        }
    }
    return 0;
}

void add_new_active_user(server_info_t *server, int new_client_fd)
{
    user_list_t *tail = server->active_users;

    if (server->active_users->next == NULL) {
        server->active_users->next = malloc(sizeof(user_list_t));
        server->active_users->next->fd = new_client_fd;
        server->active_users->next->login.passwd = NULL;
        server->active_users->next->login.username = NULL;
        server->active_users->next->login.working_dir = server->home_dir;
        server->active_users->next->next = NULL;
        return;
    }
    for ( ; tail->next; tail = tail->next);
    tail->next = malloc(sizeof(user_list_t));
    tail->next->fd = new_client_fd;
    tail->next->login.passwd = NULL;
    tail->next->login.username = NULL;
    tail->next->login.working_dir = server->home_dir;
    tail->next->next = NULL;
}

int is_user_logged_in(int client_fd, user_list_t *users)
{
    if (get_corresponding_user_info(client_fd, users).passwd == NULL || \
get_corresponding_user_info(client_fd, users).username == NULL)
        return 0;
    return 1;
}