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

typedef struct      s_gnlstrct
{
    int             fd;
    char            *storage;
    struct s_gnlstrct    *next;
}                   t_gnlstrct;

int		get_next_line(const int fd, char **line);

#endif
