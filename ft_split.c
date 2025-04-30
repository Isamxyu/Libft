/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghueso-v <ghueso-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:55:45 by ghueso-v          #+#    #+#             */
/*   Updated: 2025/04/30 03:00:25 by ghueso-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	cwords;

	cwords = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			cwords++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	cwords++;
	return (cwords);
}

static void	*ft_free(char **memry, size_t aux)
{
	size_t	i;

	i = 0;
	while (i < aux)
	{
		free(memry[i]);
		i++;
	}
	free(memry);
	return (NULL);
}

static int	split_str(char **ptr, char *str, char c, int nwords)
{
	int		i;
	char	*aux;

	i = 0;
	if ((nwords > 0) && *str)
	{
		while (i < (nwords - 1))
		{
			aux = ft_strchr(str, c);
			ptr[i] = ft_substr(str, 0, aux - str);
			if (!ptr[i])
				return (0);
			while (*aux == c)
				aux++;
			str = aux;
			i++;
		}
		ptr[i] = ft_strdup(str);
		if (!ptr[i])
			return (0);
		ptr[++i] = NULL;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*str;
	int		nwords;
	char	delimiter[2];

	if (!s)
		return (NULL);
	delimiter[0] = c;
	delimiter[1] = '\0';
	str = ft_strtrim(s, delimiter);
	if (!str)
		return (NULL);
	nwords = count_words(str, c);
	ptr = ft_calloc((nwords + 1), sizeof(char *));
	if (!ptr || !split_str(ptr, str, c, nwords))
	{
		free(str);
		if (ptr)
			ft_free(ptr, nwords);
		return (NULL);
	}
	free(str);
	return (ptr);
}
