#include "test.h"

int ft_popen(const char *file, char *const argv[], char type)
{
    int pid = -1;
    int pipe_fd[2];

    if (!file || !argv || (type != 'w' && type != 'r'))
        return -1;
    if (pipe(pipe_fd) == -1)
        return -1;
    pid = fork();
    if (pid == -1)
        return -1;
    if (pid == 0)
    {
        if (type == 'r')
        {
            if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                exit(1);
        }
        if (type == 'w')
        {
            if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
                exit(1);
        }
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        execvp(file, argv);
        exit(1);
    }
    if (type == 'r')
    {
        close(pipe_fd[1]);
        return (pipe_fd[0]);
    }
    if (type == 'w')
    {
        close(pipe_fd[0]);
        return (pipe_fd[1]);
    }
    return -1;
}