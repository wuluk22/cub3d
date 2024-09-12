#include "includes/cub3D.h"

int	nbr_of_line(int fd)
{
	int		i;
	int		nbr_line;
	char	*line;

	i = 0;
	nbr_line = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		nbr_line++;
	}
	return (nbr_line);
}

int	length_of_line(int fd)
{
	int		length;
	int		bytes;
	char	buffer[1];

	length = 0;
	bytes = 1;
	buffer[0] = '\0';
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (buffer[0] != '\n')
			length++;
		else
			break ;
	}
	return (length);
}

void	sizing_map(char **argv, t_env *e, t_map *map)
{
	int	fd;
	int	i;
	int	length_of_a_line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_exit(e, "No fd\n", 0);
	i = 0;
	map->x_map_size = 0;
	map->y_map_size = (nbr_of_line(fd));
	while (i < map->y_map_size) // a modifier
	{
		printf("a\n");
		length_of_a_line = (length_of_line(fd));
		if (length_of_a_line > map->x_map_size)
			map->x_map_size = length_of_a_line;
		i++;
	}
	close(fd);
}

int	get_map(char **argv, t_env *e, t_map *map)
{
	sizing_map(argv, e, map);
	return (0);
}
