#include "includes/cub3D.h"

void	ft_exit(t_env *e, char *str, int i)
{
	(void)e;
	(void)i;
	printf("Error\n");
	printf("%s", str);
//	if (i == 1)
//		ft_exit_window(e);
//	else
		exit (1);
}

void	free_map(char **map, int i)
{
	int	j;

	j = 0;
	while (map[j])
	{
		free(map[j]);
		map[j] = NULL;
		j++;
	}
	free(map);
	if (i == 1)
		exit (1);
}