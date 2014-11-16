/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 18:07:05 by hhismans          #+#    #+#             */
/*   Updated: 2014/11/16 01:53:43 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include "get_next_line.h"
//void		test(int const fd, char **list);

int		main(void)
{
	char *list;
	int ret;
	int i;
	i = 0;
	while (!i)
	{
		ret = get_next_line(0, &list);
	/*	if (ret == 0)
		{
			if (!(strcmp(list,"# numEntries: 30991")))
			{
				ft_putstr("ERROR");
				break;
			}
		}*/
		ft_putendl(list);
		i = 1;
	}
	/*
	ft_putstr("\n\ntest 1 ");
	ft_putendl(list);
	get_next_line(fd, &list2);
	ft_putstr("\n\ntest 2 ");
	ft_putendl(list2);
	get_next_line(fd, &list3);
	ft_putstr("\n\ntest 3 ");
	ft_putendl(list3);
*/
	return (0);
}
/*
static int where_bn(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

int		get_next_line(int const fd, char **list)
{
	static char str[BUF_SIZE];
	static int	first_step = 1;
	int ret;
	char buf[BUF_SIZE + 1];

	if(!*list)
		free(*list);
//	ft_putstr("CONTENU DE STR :");
//	ft_putendl(str);
	ft_bzero(buf,BUF_SIZE + 1);
	if (first_step)
	{
//		ft_putendl("in step 1");
		ft_bzero(str,BUF_SIZE);
//		ft_putendl("in step 1 part 2");
		first_step = 0;
	}
	if (ft_strchr(str, '\n'))
	{
		//ft_putendl("\\n IN STR");
		*list = ft_strnew(where_bn(str));
		*list = ft_strndup(str, where_bn(str));
//		ft_putstr("dup OK !");
		if (ft_strchr(str,'\n'))
		{
			ft_strcpy(str, ft_strchr(str,'\n') + 1);
		}
		else
			ft_bzero(str, BUF_SIZE);
		return (1);
	}
	else
		*list = ft_strdup(str);
	while ((ret = read(fd,buf,BUF_SIZE)))
	{
		if (ft_strchr(buf, '\n'))
		{
//			ft_putstr("find \\n BUF = ");
//			ft_putendl(buf);
//			ft_putstr("IN BUF ->\\n = ");
//			ft_putendl(ft_strchr(buf, '\n') + 1);
//			ft_putstr("END IN BUF");
			*list = ft_strnjoin(*list, buf, where_bn(buf));
		//	ft_putendl("find part 2");
			ft_strcpy(str, ft_strchr(buf, '\n') + 1);
			//ft_memmove(str, strchr(buf, '\n'), BUF_SIZE - where_nb(str));
			return (0);
		}
		else
		{
//			ft_putendl("\nNot \\n");
		//	ft_putendl(*list);
//			ft_putstr("Buf = ");
//			ft_putendl(buf);
			*list = ft_strjoin(*list, buf);
		//	ft_putendl("Not \\n part 2");
		//	ft_putstr(*list);
			//ft_putchar(*buf);
		}
	}
	//ft_putstr("quit");
	return (-1);
}*/
/*
static void where_bn(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
	}
	return (-1);
}

void		test(int const fd, char **list)
{
	static char *str = ft_memalloc(BUF_SIZE);
	char		*buf;
	int			firstread;

	firstread = 1;
	buf = strnew(BUF_SIZE);

	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		if (firstread == 1) // premier passage dans la fct
		{
			if (strchr(str,'\n'))
			{
				ft_strcpy(str,
			}
			if (strchr(buf, '\n'))
			{
				*list = ft_strcpy(*list, ft_strchr(buf,'\n'));
				ft_strncpy(str, ft_strchr(buf,'\n'));
				break;
			}
			else
			{
				ft_strcpy(*list, buf);
			}
			firstrest = 0;
		}
		if (ft_strchr(buf, '\n'))
		{
			ft_strncat(*list, buf, where_bn(buf));
			ft_strcpy(str, ft_strchr(buf,'\n'));
		}
		else
		{
			ft_strcat(
		}


		*list = str(buf);
		list
	}*/
	/*
	static t_list *lst;
	lst = ft_lstnew(NULL, 0);
	t_list *lst_temp;
	int i;
	int j;
	int ret;
	char buf[BUF_SIZE + 1];
	i = 0;
	lst_temp = lst;
	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		ft_putstr("ret = ");
		ft_putnbr(ret);
		buf[BUF_SIZE] = '\0';
		ft_putendl(buf);
		lst_temp->next = ft_lstnew(ft_strdup(buf), ft_strlen(buf) + 1);
		lst_temp = lst_temp->next;
		ft_bzero(buf, BUF_SIZE);
	}
	ft_putstr("salut");
	while (((char *)(lst_temp->content))[i])
	{
		if (((char *)(lst_temp->content))[i] == '\n')
			break;
		*list[j] = ((char *)(lst_temp->content))[i];
		if (((char *)(lst_temp->content))[i] == '\0')
		{
			i = 0;
			if (!(lst_temp->next))
				break;
			lst_temp = lst_temp->next;
		}
	}
}*/

/*
	int ret;
	char *buf;
	char *buf_temp;
	int i;

	i = 0;
	buf = ft_strnew(1000);
	buf_temp = buf;
	if (fd == -1)
	{
		ft_putstr("open() failed");
	}
	while (buf[i - BUF_SIZE] != '\n')
	{
		ret = read(fd, &buf[i], BUF_SIZE);
		i += BUF_SIZE;
		//ft_putnbr(ret);
	}

	ret = read(fd, &buf[i], BUF_SIZE);
	//ft_putstr(buf);
	*list = buf;
	return (0);
}*/
