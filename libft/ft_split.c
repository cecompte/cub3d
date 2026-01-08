/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:58:58 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/21 11:41:23 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static int	add_word(char **tab, char *s, int j, char c)
{
	int	i;
	int	k;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	tab[j] = malloc(sizeof(char) * (i + 1));
	if (!tab[j])
		return (-1);
	k = 0;
	while (k < i)
	{
		tab[j][k] = s[k];
		k++;
	}
	tab[j][k] = '\0';
	return (i);
}

static char	**process_words(char **tab, char *s, char c)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word_len = add_word(tab, &s[i], j, c);
			if (word_len == -1)
			{
				while (j > 0)
					free(tab[--j]);
				free(tab);
				return (NULL);
			}
			i += word_len;
			j++;
		}
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = count_words((char *) s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = NULL;
	return (process_words(tab, (char *)s, c));
}
