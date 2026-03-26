#include "test.h"

int ft_popen(const char *file, char *const argv[], char type)
{
    int pid = -1;
    int fd[2];

    if (!file || !argv || (type != 'r' && type != 'w'))
        return -1;
    if (pipe(fd) == -1)
        return -1;
    pid = fork();
    if (pid == -1)
        return -1;
    if (pid == 0)
    {
        if (type == 'r')
        {
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                exit(1);
        }
        if (type == 'w')
        {
            if (dup2(fd[0], STDIN_FILENO) == -1)
                exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        if (file && argv)
            execvp(file, argv);
        exit(1);
    }
    if (type == 'r')
    {
        close(fd[1]);
        return fd[0];
    }
    if (type == 'w')
    {
        close(fd[0]);
        return fd[1];
    }
    return -1;
}