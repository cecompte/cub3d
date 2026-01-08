/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:53 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/20 17:57:56 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		k = 0;
		while (s2[k] && s1[i + k] && (i + k) < n && s1[i + k] == s2[k])
			k++;
		if (s2[k] == '\0')
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
