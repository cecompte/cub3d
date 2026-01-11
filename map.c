#include "cub3d.h"

/*-Первый и последний символ строки обязаны быть '1',
иначе карта считается «протекающей» (незакрытой).


-Если текущая строка длиннее строки сверху:
Тогда все «выступающие» символы справа (те, у которых current_col > strlen(row_on_top)) должны быть '1'.
→ Это нужно, чтобы не возникало "дыр" между строками разной длины.

-Если текущая строка длиннее строки снизу:
То же самое правило — все символы правее длины нижней строки должны быть '1'.
*/
int	check_map(char *arg)
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
t_list	*get_line(int fd)
{
	t_list	*list;
	char	*line;
	t_list	*new;
	t_list	*temp;

	line = get_next_line(fd);
	list = NULL;
	while (line)
	{
		new = malloc (sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = line;
		new->next = NULL;
		if (list == NULL)
			list = new;
		else
		{
			temp = list;
			while (temp->next)
				temp = temp->next;
			temp->next = new;
		}
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

}

char	**read_map(char av[1], t_cub3d *cub)
{
	cub->map = parse_map(av, cub);
	if (!cub->map)
		return (ft_putstr_fd("Error\nCannot read map\n", 2), NULL);
	return (cub->map);
}

