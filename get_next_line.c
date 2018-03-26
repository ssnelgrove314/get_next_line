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

//function that gets the specific t_gnlfd from the t_list fdlist
//if no t_gnlfd, creates a new one and adds it to the list
static t_gnlfd	get_gnlfd(const int fd, t_list **fdlist);

//updates the next_line for the given fd.
static int		ft_set_fd_line(const int fd, char **line)
{
		char	buffer[BUF_SIZE + 1];
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

int				get_next_line(int fd, char **line)
{
	static t_list	**fdlist;
	t_gnlfd			*file;
	
	if (fd < 0 || !line)//checks for bad fd and line.
		return (-1);
	file = get_gnlfd(fd, &fdlist);
	while (!ft_strchr(file->line, '\n'))
	{
		if (ft_set_fd_line(file->fd, &file->line) < 0)
			return (-1);

		

	}
	
	
}
