int	main(void)
{
	char *line;

	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
