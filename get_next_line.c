/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:41:02 by hhismans          #+#    #+#             */
/*   Updated: 2014/11/16 03:19:25 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int		str_process(int const fd, char **line, char *str)
{
	if (ft_strchr(str, '\n'))
	{
		*line = ft_strndup(str, ft_strchri(str, '\n'));
		if (ft_strchr(ft_strchr(str, '\n'), '\n'))
			ft_strcpy(str, ft_strchr(str, '\n') + 1);
		else
			ft_bzero(str, BUFF_SIZE);
		return (1);
	}
	else
	{
		*line = ft_strdup(str);
		ft_bzero(str,BUFF_SIZE);
		return (0);
	}
}

static int		buf_process(int const fd, char **line, char *str)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char *tmp; //test

	ft_bzero(buf, BUFF_SIZE + 1);
	tmp = *line;
	*line = ft_strjoin(*line, str);
	free(tmp);
	ft_bzero(str, BUFF_SIZE);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ft_strchr(buf, '\n'))
		{
			tmp = *line;
			*line = ft_strnjoin(*line, buf, ft_strchri(buf, '\n'));
			free(tmp);
			ft_strcpy(str, ft_strchr(buf, '\n') + 1);
			return (1);
		}
		else
		{
			*line = ft_strjoin(*line, buf);
		}
	}
	if (ft_strchr(buf, '\n'))
	{
		tmp = *line;
		*line = ft_strnjoin(*line, buf, ft_strchri(buf, '\n'));
		free(tmp);
		ft_strcpy(str, ft_strchr(buf, '\n') + 1);
		return (1);
	}
	else
	{
			tmp = *line;
		*line = ft_strjoin(*line, buf);
			free(tmp);
	}


	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*str[256];
	static int	first_step[256] = {0};
	int i;
	i = 0;

	if (BUFF_SIZE > 8000000)
	{
		ft_putendl_fd("Error, BUFF_SIZE is too big", 2);
		return (-1);
	}
	if (!first_step[fd])
	{
		(str)[fd] = (char *)ft_memalloc(BUFF_SIZE);
		first_step[fd] = 1;
	}
	if (str_process(fd, line, str[fd]))
	{
		return (1);
	}
	if (buf_process(fd, line, str[fd]))
		return (1);
	free(str[fd]);
	return (0);
}
