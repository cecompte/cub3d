#include "cub3d.h"

/*-Первый и последний символ строки обязаны быть '1',
иначе карта считается «протекающей» (незакрытой).

-Если текущая строка длиннее строки сверху:
Тогда все «выступающие» символы справа (те, у которых current_col > strlen(row_on_top)) должны быть '1'.
→ Это нужно, чтобы не возникало "дыр" между строками разной длины.

-Если текущая строка длиннее строки снизу:
То же самое правило — все символы правее длины нижней строки должны быть '1'.
*/
int	check_map(char **arg)
{
	(void)arg;
	return (0);
}

int	extension_map(int ac, char **av)
{
	char	*ptr;

	ptr = av[1];
	if (ac == 2)
	{
		while (*ptr && (ft_strncmp(ptr, ".cub", 4) != 0))
			ptr++;
		if (!(*ptr))
			return (1);
		ptr += 4;
		if (*ptr == '\0')
			return (0);
		else
			return (1);
	}
	return (1);
}

char	**convert_list_to_array(t_list *list)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(list);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (list)
	{
		arr[i] = list->content;
		list = list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*get_line(int fd)
{
	t_list	*list;
	t_list	*new;
	char	*line;

	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new = ft_lstnew(line);
		if (!new)
		{
			free(line);
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		line = get_next_line(fd);
	}
	return (list);
}

char	**parse_map(char *av, t_cub3d *cub)
{
	int		fd;
	t_list	*list;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	list = get_line(fd);
	close(fd);
	if (!list)
		return (NULL);
	cub->map = convert_list_to_array(list);
	ft_lstclear(&list, NULL);
	if (!cub->map)
		return (NULL);
	if (check_map(cub->map) != 0)
		return (ft_putstr_fd("Error\nMap is not valid\n", 2), NULL);
	return (cub->map);

}

char	**read_map(char av[1], t_cub3d *cub)
{
	cub->map = parse_map(av, cub);
	if (!cub->map)
		return (ft_putstr_fd("Error\nCannot read map\n", 2), NULL);
	return (cub->map);
}

