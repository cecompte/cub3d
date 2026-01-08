/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:22:11 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/20 12:47:32 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*res;
	char		*start;
	const char	*p1;
	const char	*p2;

	p1 = s1;
	p2 = s2;
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	start = res;
	while (*p1)
		*res++ = *p1++;
	while (*p2)
	*res++ = *p2++;
	*res = '\0';
	return (start);
}
