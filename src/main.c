#include "../includes/cub3d.h"

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (0);
	}
	if (!check_map(av[1]))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (!check_arguments(ac, av))
		return (1);

}
