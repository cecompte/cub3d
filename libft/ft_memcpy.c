/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:58:59 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/20 15:32:30 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned const char	*buf;
	unsigned char		*res;

	if (n == 0 || dest == src)
		return (dest);
	buf = (unsigned const char *)src;
	res = (unsigned char *)dest;
	while (n--)
	{
		*res = *buf;
		res++;
		buf++;
	}
	return (dest);
}
