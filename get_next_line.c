/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnelgro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 20:37:06 by ssnelgro          #+#    #+#             */
/*   Updated: 2018/03/25 01:48:41 by ssnelgro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A "line" is a succession of characters that end with '\n' (ascii code 0x0a)
** or with End Of File (EOF)
**
** @Param1: file descriptor that will be used to read
** @Param2: the address of a pointer to a character that will be used to save
** the line read from the fd.
** @Return: Value can be 1, 0 or -1
** 1: line was read
** 0: reached EOF
** -1: something fucked up
**
** the line must not contain the '\n' character.
** Call this function in a loop to read through a file one line at a time.
*/

#include "get_next_line.h"

static int		lineset(const int fd, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	if ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(tmp, buffer);
		ft_strdel(&tmp);
	}
	return (ret);
}

static t_gnlfd	*determine_file(const int fd, t_gnlfd **master_list)
{
	t_gnlfd *ptr;

	ptr = *master_list;
	while (ptr && ptr->fd != fd)
		ptr = ptr->next;
	if (!ptr)
	{
		ptr = (t_gnlfd *)ft_memalloc(sizeof(t_gnlfd));
		ptr->fd = fd;
		if (!(ptr->line = ft_strnew(0)))
			return (NULL);
		ptr->next = *master_list;
		*master_list = ptr;
	}
	return (ptr);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnlfd	*master_list;
	t_gnlfd			*f;
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);
	f = determine_file(fd, &master_list);
	LINCHK(f->line);
	while (!(ft_strchr(f->line, '\n')))
	{
		if (lineset(f->fd, &f->line) < 0)
			return (-1);
		if (!(lineset(f->fd, &f->line)) && (!(ft_strchr(f->line, '\n'))))
		{
			LINCHK(f->line[0]);
			*line = f->line;
			f->line = NULL;
			return (1);
		}
	}
	*line = ft_strsub(f->line, 0, (ft_strchr(f->line, '\n') - f->line));
	tmp = f->line;
	f->line = ft_strdup(ft_strchr(f->line, '\n') + 1);
	ft_strdel(&tmp);
	return (1);
}
