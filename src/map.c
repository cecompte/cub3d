#include "cub3d.h"

int	check_extension(char *str, char *ext)
{
	int	len;
	int	ext_len;

	if (!str)
		return (1);
	len = ft_strlen(str);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (1);
	if (ft_strncmp(str - len + ext_len, ext_len, ext) == 0)
		return (0);
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
	return (cub->map);

}

char	**read_map(char av[1], t_cub3d *cub)
{
	cub->map = parse_map(av, cub);
	if (!cub->map)
		return (ft_putstr_fd("Error\nCannot read map\n", 2), NULL);
	return (cub->map);
}

