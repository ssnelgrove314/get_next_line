#include "get_next_line.h"

static t_gnlstrct  *gnl_determine_file(const int fd, t_gnlstrct **line_list)
{
    t_gnlstrct  *ptr;

    ptr = *line_list;
    while (ptr && ptr->fd != fd)
        ptr = ptr->next;
    if (!ptr)
    {
        ptr = (t_gnlstrct *)ft_memalloc(sizeof(t_gnlstrct));
        ptr->fd = fd;
        ptr->storage = ft_strnew(0);
        ptr->next = *line_list;
    }
    return (ptr);
}

static char    *gnl_readline(t_gnlstrct *f)
{
    char *buffer;
    int ret;

    buffer = ft_strnew(BUFF_SIZE + 1);
    ret = 0;
    if (!f->storage)
        f->storage = ft_strnew(1);
    while (!(ft_strchr(f->storage, '\n')))
    {
        ret = read(f->fd, buffer, BUFF_SIZE);
        buffer[ret] = '\0';
        f->storage = ft_strjoin(f->storage, buffer);
    }
    ft_strdel(&buffer);
    return (f->storage);
}

static char *gnl_search_storage(t_gnlstrct *f)
{
    char *remaining;
    char *result;
    int length;

    remaining = ft_strchr(f->storage, '\n');
    if (!remaining)
    {
        f->storage = gnl_readline(f);
        gnl_search_storage(f);
    }
    remaining++;
    remaining = ft_strdup(remaining);
    length = ft_strlen(f->storage) - ft_strlen(remaining);
    result = ft_strnew(length);
    ft_strlcpy(result, f->storage, length + 1);
    ft_strdel(&(f->storage));
    f->storage = remaining;
    return (result);
}

int		get_next_line(const int fd, char **line)
{
    static t_gnlstrct       **file_list;
    t_gnlstrct              *file;
    int                     size_of_line;
    char                    *next_line;

    size_of_line = 0;
    file = gnl_determine_file(fd, file_list);
    if (!file->storage)
        file->storage = gnl_readline(file);
    next_line = gnl_search_storage(file);
    size_of_line = ft_strlen(next_line);
    ft_strlcpy(*line, next_line, size_of_line + 1);
    ft_strdel(&next_line);
    return (size_of_line);
}
