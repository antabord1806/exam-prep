#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *get_next_line(int fd);
int ft_popen(const char *file, char *const argv[], char type);

#endif