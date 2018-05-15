#include "get_next_line.h"

static int		lineset(const int fd, t_gnl *f)
{
	char	*buffer;
	int		ret;
    char    *tmp;

    buffer = ft_strnew(BUFF_SIZE + 1);
	if ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
        tmp = f->storage;
		f->storage = ft_strjoin(f->storage, buffer);
        ft_strdel(&tmp);
	}
    ft_strdel(&buffer);
	return (ret);
}

static t_gnl	*determine_file(const int fd, t_gnl **master_list)
{
	t_gnl *ptr;

	ptr = *master_list;
	while (ptr && ptr->fd != fd)
		ptr = ptr->next;
	if (!ptr)
	{
		ptr = (t_gnl *)ft_memalloc(sizeof(t_gnl));
		ptr->fd = fd;
        if (!(ptr->storage = ft_strnew(0)))
            return (NULL);
		ptr->next = *master_list;
		*master_list = ptr;
	}
	return (ptr);
}

static int          set_storage_and_line(t_gnl *f, char **line)
{
    int i;
    char *tmp;

    i = 0;
    tmp = NULL;
	while (!(ft_strchr(f->storage, '\n')))
	{
        i = lineset(f->fd, f);
		if (i < 0)
			return (-1);
		if (!i && (!(ft_strchr(f->storage, '\n'))))
		{
			LINCHK(f->storage[0]);
            *line = f->storage;
			return (1);
		}
	}
	*line = ft_strsub(f->storage, 0, (ft_strchr(f->storage, '\n') - f->storage));
    tmp = f->storage;
	f->storage = ft_strdup(ft_strchr(f->storage, '\n') + 1);
	ft_strdel(&tmp);
    return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*master_list;
	t_gnl			*f;

	if (fd < 0 || !line)
		return (-1);
	f = determine_file(fd, &master_list);
    LINCHK(f->storage);
    return (set_storage_and_line(f, line));
}
