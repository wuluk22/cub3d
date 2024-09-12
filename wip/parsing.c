#include "includes/cub3D.h"

int	check_name(char *map_name)
{
	if (ft_strnstr(map_name, ".cub\0", ft_strlen(map_name)))
		return (0);
	return (1);
}

int	parsing(int argc, char **argv, t_map *map, t_env *e)
{
	if (argc != 2)
        ft_exit(e, "Not a number of arguments allowed\n", 0);
	printf("nmbr of argc ok\n");
    if (check_name(argv[1]) == 1)
		ft_exit(e, "Not a valid name\n", 0);
	printf("name of file ok\n");
//   get_info(&e, argv);
   get_map(argv, e, map);
	return (0);
}

// e->map_x
// e->map_y
// e->map_height 
// e->map_width
