#include "test.h"

/* int main()
{
    int  fd;
    char *line;

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((line = get_next_line(fd)))
        puts(line);
    close(fd);
    return (0);
} */


int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
    fd = ft_popen("wc", (char *const []){"wc", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("grep", (char *const []){"grep","c", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    fd = ft_popen("wc", (char *const []){"wc", NULL}, 'r');
	while ((line = get_next_line(fd)))
		printf("%s", line);
    close(fd);
}

/* #include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd;
    char *line;

    printf("=== Test 1: ls | grep c ===\n");
    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)))
        printf("%s", line);
    close(fd);
    wait(NULL);

    printf("\n=== Test 2: echo hello ===\n");
    fd = ft_popen("echo", (char *const []){"echo", "hello world", NULL}, 'r');
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)))
        printf("%s", line);
    close(fd);
    wait(NULL);

    printf("\n=== Test 3: Multiple sequential popen ===\n");
    for (int i = 0; i < 3; i++)
    {
        fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
        if (fd == -1)
            return (1);
        int count = 0;
        while ((line = get_next_line(fd)) && count < 2)
        {
            printf("%s", line);
            count++;
        }
        close(fd);
        wait(NULL);
    }

    printf("\nAll tests completed.\n");
    return (0);
} */
/* 
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int test_read_mode(void)
{
    printf("=== Test 1: Read mode (ls) ===\n");
    int fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    if (fd == -1)
        return (printf("FAIL: ft_popen returned -1\n"), 1);
    char *line;
    int count = 0;
    while ((line = get_next_line(fd)) && count < 5)
    {
        printf("%s", line);
        count++;
    }
    close(fd);
    wait(NULL);
    printf("PASS: Read %d lines\n\n", count);
    return (0);
}

int test_write_mode(void)
{
    printf("=== Test 2: Write mode (cat) ===\n");
    int fd = ft_popen("cat", (char *const []){"cat", NULL}, 'w');
    if (fd == -1)
        return (printf("FAIL: ft_popen returned -1\n"), 1);
    const char *test_str = "Hello from write mode\n";
    ssize_t written = write(fd, test_str, strlen(test_str));
    close(fd);
    wait(NULL);
    printf("PASS: Wrote %ld bytes\n\n", written);
    return (0);
}

int test_invalid_file(void)
{
    printf("=== Test 3: Invalid file ===\n");
    int fd = ft_popen("/nonexistent/command", (char *const []){"cmd", NULL}, 'r');
    if (fd == -1)
    {
        printf("PASS: Correctly returned -1\n\n");
        return (0);
    }
    close(fd);
    wait(NULL);
    printf("FAIL: Should have returned -1\n\n");
    return (1);
}

int test_null_args(void)
{
    printf("=== Test 4: NULL arguments ===\n");
    int fd1 = ft_popen(NULL, (char *const []){"ls", NULL}, 'r');
    int fd2 = ft_popen("ls", NULL, 'r');
    int fd3 = ft_popen("ls", (char *const []){"ls", NULL}, 'x');
    
    if (fd1 == -1 && fd2 == -1 && fd3 == -1)
    {
        printf("PASS: All NULL cases returned -1\n\n");
        return (0);
    }
    printf("FAIL: Should all return -1\n\n");
    return (1);
}

int test_multiple_sequential(void)
{
    printf("=== Test 5: Multiple sequential popen ===\n");
    for (int i = 0; i < 5; i++)
    {
        int fd = ft_popen("echo", (char *const []){"echo", "test", NULL}, 'r');
        if (fd == -1)
            return (1);
        char *line = get_next_line(fd);
        if (line)
            printf("Iteration %d: %s", i + 1, line);
        close(fd);
        wait(NULL);
    }
    printf("PASS: All iterations completed\n\n");
    return (0);
}

int main(void)
{
    int failed = 0;

    printf("========== FT_POPEN EDGE CASE TESTS ==========\n\n");

    failed += test_read_mode();
    failed += test_write_mode();
    failed += test_invalid_file();
    failed += test_null_args();
    failed += test_multiple_sequential();

    printf("========== SUMMARY ==========\n");
    printf("Tests failed: %d\n\n", failed);

    return (failed > 0 ? 1 : 0);
} */