/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:41:02 by hhismans          #+#    #+#             */
/*   Updated: 2014/11/16 01:16:32 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line2.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int		str_process(char **line, char *str,int i)
{
	if (ft_strchr(str, '\n'))
	{
		*line = ft_strndup(str, ft_strchri(str, '\n'));
		if (ft_strchr(ft_strchr(str, '\n'), '\n'))
			ft_strcpy(str, ft_strchr(str, '\n') + 1);
		else
			ft_bzero(str, BUFF_SIZE + i);
		return (1);
	}
	else
	{
		*line = ft_strdup(str);
		ft_bzero(str,BUFF_SIZE + i);
		return (0);
	}
}

static int		buf_process(int const fd, char **line, char *str,int i)
{
	char	buf[BUFF_SIZE + i + 1];
	int		ret;
	char *line_temp;
	ft_bzero(buf, BUFF_SIZE + i + 1);
	line_temp = *line;
	*line = ft_strjoin(*line, str);
	free(line_temp);
	ft_bzero(str, BUFF_SIZE + i);
	while ((ret = read(fd, buf, BUFF_SIZE + i)))
	{
		if (ft_strchr(buf, '\n'))
		{
			line_temp = *line;
			*line = ft_strnjoin(*line, buf, ft_strchri(buf, '\n'));
			free(line_temp);
			ft_strcpy(str, ft_strchr(buf, '\n') + 1);
			return (1);
		}
		else
		{
			line_temp = *line;
			*line = ft_strjoin(*line, buf);
			free(line_temp);
		}
	}
		if (ft_strchr(buf, '\n'))
		{
			line_temp = *line;
			*line = ft_strnjoin(*line, buf, ft_strchri(buf, '\n'));
			free(line_temp);
			ft_strcpy(str, ft_strchr(buf, '\n') + 1);
			return (1);
		}
		else
		{
			line_temp = *line;
			*line = ft_strjoin(*line, buf);
			free(line_temp);
		}

	return (0);
}

int				get_next_line(int const fd, char **line, int i)
{
	static char	str[10000000];
	static int	first_step = 1;
//	ft_putstr("size of :");
//	ft_putnbr((int)sizeof(str));
//	ft_putendl(" ");

	if (BUFF_SIZE + i > 8000000)
	{
		ft_putendl_fd("Error, BUFF_SIZE + i is too big", 2);
		return (-1);
	}
	if (!*line)
		free(*line);
	if (first_step)
	{
		ft_bzero(str, BUFF_SIZE + i);
		first_step = 0;
	}
	if (str_process(line,str,i))//if (ft_strchr(str, '\n'))
	{
		//str_process(line, str);
		return (1);
	}
/*	else if (*str != '\0')
	{
		ft_putstr("aslut");
		*line = ft_strjoin(*line, str);
		ft_bzero(str,BUFF_SIZE + i);
	}*/
	if (buf_process(fd, line, str,i))
		return (1);
	ft_bzero(str,BUFF_SIZE + i);
	return (0);
}
