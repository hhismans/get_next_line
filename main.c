/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:02:40 by yfuks             #+#    #+#             */
/*   Updated: 2014/11/15 06:34:42 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "get_next_line.h"
#include <signal.h>

char	*file;

void sighandler(int signum)
{
	printf("Test with \033[34m%s\033[37m = [\033[31mSegfault\033[37m] got signal %d\n",file , signum);
    signal(signum, SIG_DFL);
    kill(getpid(), signum);
}

int main(int argc, char ** argv)
{
	int fd;
	int fd2;
	char *line;
	char BUFF1[10];
	char BUFF2[10];

	signal(SIGSEGV, sighandler);
	if (argc < 2)
	{
		if (isatty(fileno(stdin)))
			printf("You can also test stdin with\n%% > \033[33mecho \"Test\\ntest2\\n\" | %s \033[37m\n\n", argv[0]);
		else
			printf("You can also test stdin with \033[37m\n%% > \033[33m%s\033[037m\n[\033[33mthen enter some texte\033[37m]\n\n", argv[0]);
		fd = 0;
		file = strdup("stdin");
	}
	else
	{
		fd = open(argv[1], O_RDWR);
		file = argv[1];
	}
	fd2 = open("trace.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1 || fd2 == -1)
	{
		perror("open");
		close(fd);
		close(fd2);
		return (-1);
	}
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		write(fd2, "\n", 1);
		printf("line received = \"%s\"\n", line);
		free(line);
	}
	printf ("\033[37mTest with \033[36m%s \033[37m= ", file);
	memset(BUFF1, '\0', 10);
	memset(BUFF2, '\0', 10);
	while (read(fd, BUFF1, 10))
	{
		read(fd2, BUFF2, 10);
		if ((memcmp(BUFF1, BUFF2, 10)) != 0)
		{
			printf("[\033[31mFAILED\033[37m]\n");
			printf("\033[31mGet :\n\033[37m\"%s\"\n\033[31mNeed :\n\033[37m\"%s\"\n", BUFF2, BUFF1);
			break;
		}
	}
	if ((memcmp(BUFF1, BUFF2, 10)) == 0)
		printf("[\033[32mLooks OK\033[37m]\n");
	close(fd);
	close(fd2);
	if (argc > 2)
		printf("\n\033[35mThis \033[31ms\033[32mh\033[33m\033[34mi\033[35mt\033[36mw\033[31ma\033[32mr\033[33me \033[35m(GNU licensed) can only handle one argument, monde de merde.\n");
	return (0);
}
