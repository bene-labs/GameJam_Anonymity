/*
** EPITECH PROJECT, 2024
** Ftp
** File description:
** Created by benedikt,
*/

#include "include/ftp.h"

int set_corresponding_dir(int client_fd, char *path, \
user_list_t *users)
{
    for (user_list_t *temp = users->next; temp; temp = temp->next) {
        if (temp->fd == client_fd) {
            temp->login.working_dir = path;
            return 1;
        }
    }
    return 0;
}

int remove_corresponding_user(int client_fd, user_list_t *users)
{
    for (user_list_t *temp = users; temp->next; temp = temp->next) {
        if (temp->next->fd == client_fd) {
            user_list_t *save = temp->next->next;
            free(temp->next);
            temp->next = save;
            return 1;
        }
    }
    return 0;
}