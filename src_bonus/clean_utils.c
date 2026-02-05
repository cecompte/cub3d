/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:24 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/05 12:03:36 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	free_error(char **map, char **map2, char *message)
{
	free_tabc(map);
	free_tabc(map2);
	ft_putstr_fd(message, 2);
	return (1);
}
