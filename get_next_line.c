#include "get_next_line.h"

/*
** @Function: appends the data read into buffer to f->storage
** @Param 1: The gnl structure.
** @Return: the length of the data read in.
*/

static int		lineset(t_gnl *f)
{
	char	*buffer;
	int		ret;
    char    *tmp;

    buffer = ft_strnew(BUFF_SIZE + 1);
	if ((ret = read(f->fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
        tmp = f->storage;
		f->storage = ft_strjoin(f->storage, buffer);
        ft_strdel(&tmp);
	}
    ft_strdel(&buffer);
	return (ret);
}

/*
** @Function: Determines the list element associated with
** @Param 1: the t_gnl pointer, whose member f->storage will be changed.
** @Param 2: The string pointer to be set to the buffer storing the newline.
** @Return: Same values as get_next_line
*/

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

/*
** @Function: Sets the storage to the remaining part of the storage and
** sets the line to the next_line.
** @Param 1: the t_gnl pointer, whose member f->storage will be changed.
** @Param 2: The string pointer to be set to the buffer storing the newline.
** @Return: Same values as get_next_line
*/

static int          set_storage_and_line(t_gnl *f, char **line)
{
    int i;
    char *tmp;

    i = 0;
    tmp = NULL;
	while (!(ft_strchr(f->storage, '\n')))
	{
        i = lineset(f);
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

/*
** @Function: Gets the next line from the file descriptor fd and stores it in
** a buffer pointed to by line. Handles multiple file descriptors and stores
** them as a Linked List. The head of the list is a static variable master_list
** that maintains the list between function calls.
** @Param 1: The file descriptor to read, obtained by opening a path with open
** @Param 2: The pointer to the buffer that gnl uses to store the next line.
** @Return: Returns 1 if line has been read, 0 if the reading is completed and
** -1 if an error occurs.
*/

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
