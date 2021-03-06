/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnelgro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 00:57:48 by ssnelgro          #+#    #+#             */
/*   Updated: 2018/03/25 01:07:17 by ssnelgro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

#define LINCHK(x) if (!x) return (0);

typedef struct      s_gnl
{
    int             fd;
    char            *storage;
    struct s_gnl    *next;
}                   t_gnl;

int		get_next_line(const int fd, char **line);

#endif
