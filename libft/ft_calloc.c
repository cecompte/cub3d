/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:53 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/19 17:22:44 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	if (size != 0 && num > (SIZE_MAX / size))
		return (NULL);
	arr = malloc(size * num);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, (num * size));
	return (arr);
}
