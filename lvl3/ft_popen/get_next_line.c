#include "test.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

#ifndef NULL
#define NULL (*(void))
#endif

static char *ft_strjoin(char *tmp, char *buffer)
{
    int tmp_len = 0;

    if (tmp)
    {
        while (tmp[tmp_len])
            tmp_len++;
    }
    int buffer_len = 0;
    if (buffer)
    {
        while (buffer[buffer_len])
            buffer_len++;
    }
    else
        return NULL;
    //printf("buffer_len %d\n", buffer_len);
    char *str = malloc(buffer_len + tmp_len + 1);
    if (!str)
        return NULL;
    for (int i = 0; i < tmp_len; i++)
        str[i] = tmp[i];
    for (int i = 0; i < buffer_len; i++)
        str[tmp_len + i] = buffer[i];
    str[tmp_len + buffer_len] = '\0';
    //printf("str: %s\n", str);
    return str;
}

static int finding_nl(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            //printf("found nl\n");
            return 1;
        }
        i++;
    }
    return 0;
}
static char *get_line(char *tmp, char *buffer)
{
    int tmp_len = 0;
    //printf("tmp %s\n", tmp);
    while (tmp[tmp_len] && tmp[tmp_len] != '\n')
        tmp_len++;
    if (tmp[tmp_len] == '\n')
        tmp_len++;
    char *str = malloc(tmp_len + 1);
    if (!str)
        return NULL;
    for (int i = 0; i < tmp_len; i++)
        str[i] = tmp[i];
    str[tmp_len] = '\0';
    int i = 0;
    while (tmp[tmp_len + i])
    { 
        buffer[i] = tmp[tmp_len + i];
        i++;
    }
    buffer[i] = '\0';
    //printf("line %s\n", str);
    return str;
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    int bytes_read = 1;
    char *tmp = NULL;
    char *old_tmp = NULL;

    if (buffer[0])
    {
        tmp = ft_strjoin(NULL, buffer);
        buffer[0] = '\0';
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        //printf("tmp: %s\n", tmp);
        if (!tmp)
            break;
        free(old_tmp);
        if (finding_nl(tmp))
            break;
    }
    if (tmp && finding_nl(tmp))
    {
        char *line = get_line(tmp, buffer);
        free(tmp);
        return (line);
    }
    if (tmp && !finding_nl(tmp))
        return tmp;
    free(tmp);
    return NULL;
}