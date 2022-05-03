/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argvsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:27:12 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/03 19:52:00 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countspecial(char const *str, int i)
{
	if (str[i] == '\'' )
	{
		i++;
		while (str[i] != '\'' && str[i] != '\0')
			i++;
		i++;
	}
	else if (str[i] == '\"' )
	{
		i++;
		while (str[i] != '\"' && str[i] != '\0')
			i++;
		i++;
	}
	return (i);
}

static int	ft_count(char const *str)
{
	int	cpal;
	int	i;

	cpal = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		i = ft_countspecial(str, i);
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		if (str[i] == ' ' || str[i] == '\0')
			cpal++;
	}
	return (cpal);
}

static int	ft_countj(const char *str, int i)
{
	int	com;

	com = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '\'' )
		{
			com++;
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
		}
		else if (str[i] == '\"' )
		{
			com++;
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (i - com * 2);
}

static char	**ft_split2(const char *str, char **result, int l)
{
	int		*i;

	i = malloc(sizeof(int) * 3);
	i[0] = 0;
	while (str[i[0]] != '\0' && l < ft_count(str))
	{
		i[2] = 0;
		while (str[i[0]] == ' ')
			i[0]++;
		i[1] = ft_countj(str, i[0]);
		result[l] = malloc((i[1] - i[0] + 1) * sizeof(char));
		if (!result)
			return (ft_free(result));
		i = ft_splitcopyspecial(str, result, i, l);
		result[l][i[2]] = '\0';
		l++;
	}
	result[l] = NULL;
	free(i);
	return (result);
}

char	**ft_argvsplit(char const *str)
{
	int		l;
	char	**result;

	l = 0;
	if (!str)
		return (NULL);
	result = malloc((ft_count(str) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_split2(str, result, l);
	return (result);
}
