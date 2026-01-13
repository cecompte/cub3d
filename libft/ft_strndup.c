/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:17:31 by cecompte          #+#    #+#             */
/*   Updated: 2025/09/11 15:18:20 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	if (!s1[0])
		return (NULL);
	len = ft_strlen(s1);
	if (len < n)
		n = len + 1;
	ptr = ft_calloc(n + 1, 1);
	if (!ptr)
		return (NULL);
	i = 0;
	if (n > 0)
	{
		while (s1[i] && i < n)
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
