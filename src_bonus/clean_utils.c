#include "cub3d_bonus.h"

void	free_tabc(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


void	free_nodes(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	free_array(int **arr, int height)
{
	int	y;

	y = 0;
	if (!arr)
		return ;
	while (y < height)
	{
		free(arr[y]);
		y++;
	}
	free(arr);
}
