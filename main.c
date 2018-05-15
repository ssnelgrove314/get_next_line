#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char *str;

    fd = 0;
    str = ft_strnew(200);
    if (argc < 2)
    {
        ft_putendl("Error, test with files");
        return (0);
    }
    fd = ft_fopen(argv[1], "r+");
    get_next_line(fd, &str);
    ft_putendl(str);
    get_next_line(fd, &str);
    ft_putendl(str);
    get_next_line(fd, &str);
    ft_putendl(str);
    get_next_line(fd, &str);
    ft_putendl(str);
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
