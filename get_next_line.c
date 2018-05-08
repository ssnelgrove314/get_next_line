#include "get_next_line.h"

t_list  *gnl_determine_file(const int fd, char **line, t_list **line_list)
{
    t_list  *new;

    new = *line_list;
    if (!(*line_list))
        new = ft_lstappend(line_list, NULL, fd);
    while (new && new->content_size != fd)
        new = new->next;
    if (!new)
        new = ft_lstappend(line_list, NULL, (size_t)fd);
    return (new);
}

char    *gnl_readline(t_list *f)
{
    char *storage;
    char *buffer;
    int ret;

    storage = (char *)f->content;
    buffer = ft_strnew(BUFF_SIZE + 1);
    ret = 0;
    if (!storage)
        storage = ft_strnew(0);
    while (!ft_strchr(storage, '\n'))
    {
        ret = read(f->content_size, buffer, BUFF_SIZE);
        buffer[ret] = '\0';
        ft_strjoin(storage, buffer);
    }
    f->content = (void *)storage;
    ft_strdel(&buffer);
    return (f->content);
}

char *gnl_search_storage(t_list *f)
{
    char *remaining;
    char *result;
    int length;

    remaining = ft_strchr((char *)f->content, '\n');
    remaining++;
    remaining = ft_strdup(remaining);
    length = ft_strlen((char *)f->content) - ft_strlen(remaining);
    ft_strlcpy(result, (char *)f->content, length);
    ft_strdel(&(char *)f->content);
    f->content = remaining;
    return (result);
}

int		get_next_line(const int fd, char **line)
{
    static t_list   **line_list;
    t_list          *f;
    int             size_of_line;
    char            *next_line;

    size_of_line = 0;
    f = gnl_determine_file(fd, line, line_list);
    if (!ft_strchr((char *)f->content, '\n'))
        f->content = (void *)gnl_readline(f);
    next_line = gnl_search_storage(f);
    size_of_line = ft_strlen(next_line);
    write(1, next_line, size_of_line);
    ft_strdel(&next_line);
    return (size_of_line);
}
