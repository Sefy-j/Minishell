/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:06:19 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/04 15:03:54 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_nbr_words2(char const *s1, char c)
{
	size_t	nbr_wrds;
	char	quotes;

	if (*s1)
		nbr_wrds = 1;
	else 
		nbr_wrds = 0;
	quotes = 0;
	while (*s1)
	{
		if (*s1 == '\'' || *s1 == '"')
		{
			if (quotes == 0)
				quotes = *s1;
			else if (*s1 == quotes)
				quotes = 0;
		}
		if (quotes == 0 && *s1 == c)
		{
			nbr_wrds++;
			while (*s1 == c && *s1)
				s1++;
		}
		else
			s1++;
	}
	return (nbr_wrds);
}

static int	ft_lenchar2(char *s1, char c)
{
	int		j;
	char	quotes;

	j = 0;
	quotes = 0;
	while ((*s1 != c || quotes != 0) && *s1)
	{
		if (*s1 == '\'' || *s1 == '"')
		{
			if (quotes == 0)
				quotes = *s1++;
			else if (*s1 == quotes)
			{
				quotes = 0;
				s1++;
			}
		}
		if (*s1)
		{
			s1++;
			j++;
		}
	}
	return (j);
}

static char	**ft_aux_split2(size_t nbr_wrds, char const *s1,
	char c, char **wrds)
{
	int		i;
	int		j;
	int		length;
	char	quotes;

	i = 0;
	quotes = 0;
	while (nbr_wrds--)
	{
		while (*s1 == c)
			s1++;
		length = ft_lenchar2((char *)s1, c);
		wrds[i] = malloc(sizeof(char) * (length + 1));
		j = 0;
		while (length-- > 0)
		{
			if (*s1 == '\'' || *s1 == '"')
			{
				if (quotes == 0)
					quotes = *s1++;
				else if (quotes == *s1)
				{
					quotes = 0;
					s1++;
				}
			}
			if (*s1 && *s1 != quotes)
				wrds[i][j++] = *s1++;
		}
		wrds[i][j] = '\0';
		i++;
	}
	wrds[i] = NULL;
	return (wrds);
}

char	**ft_split_cmds(char const *s1, char c)
{
	size_t	nbr_wrds;
	char	**words;

	if (!s1)
		return (NULL);
	while (*s1 == c && *s1)
		s1++;
	nbr_wrds = ft_nbr_words2(s1, c);
	words = malloc(sizeof(char *) * (nbr_wrds + 1));
	if (!words)
		return (NULL);
	words = ft_aux_split2(nbr_wrds, s1, c, words);
	return (words);
}
