#include "get_next_line.h"

int main(int argc, char **argv)
{
    char *str;
    char *str2;
    int fd;
    int fd2;

    fd = fd2 = 0;
    if (argc < 2)
    {
        ft_putendl("Error, test with files");
        return (0);
    }
    fd = ft_fopen(argv[1], "r+");
    fd2 = ft_fopen(argv[2], "r+");
    while (get_next_line(fd, &str) > 0 && get_next_line(fd2, &str2) > 0)
    {
        ft_putendl(str);
        ft_putendl(str2);
        ft_strdel(&str);
    }
    close (fd);
    close (fd2);
    return (0);

/*
    for (int i = 1; i < argc; i++)
    {
        fd = ft_fopen(argv[i], "r+");
        while (get_next_line(fd, &str) > 0)
            ft_putendl(str);
        close(fd);
    }
    return (0);
*/
}
