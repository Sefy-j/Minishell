/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:39:43 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/03 19:52:15 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_splitcopy(const char *str, char **result, int *i, int l)
{
	result[l][i[2]] = str[i[0]];
	i[0]++;
	i[2]++;
	return (i);
}

int	*ft_splitcopyspecial(const char *str, char **result, int *i, int l)
{
	while (str[i[0]] != ' ' && str[i[0]] != '\0')
	{
		if (str[i[0]] == '\'' )
		{
			i[0]++;
			while (str[i[0]] != '\'' && str[i[0]] != '\0')
				i = ft_splitcopy(str, result, i, l);
			i[0]++;
		}
		else if (str[i[0]] == '\"' )
		{
			i[0]++;
			while (str[i[0]] != '\"' && str[i[0]] != '\0')
				i = ft_splitcopy(str, result, i, l);
			i[0]++;
		}
		else
			i = ft_splitcopy(str, result, i, l);
	}
	return (i);
}

static char	*get_those_quotes(char *read, char quotes)
{
	char	*new_read;
	char	*p;
	char	*q;

	p = read;
	read = ft_strjoin(read, "\n");
	free(p);
	new_read = readline("> ");
	while (!ft_strchr(new_read, (int)quotes))
	{
		p = new_read;
		new_read = ft_strjoin(new_read, "\n");
		free(p);
		q = readline("> ");
		p = new_read;
		new_read = ft_strjoin(p, q);
		free(p);
		free(q);
	}
	p = read;
	read = ft_strjoin(read, new_read);
	free(new_read);
	free(p);
	return (read);
}

char	*check_those_quotes(char *read)
{
	char	quotes;
	int		i;

	quotes = 0;
	i = 0;
	while (read[i])
	{
		if ((read[i]== '\'' || read[i] == '"') && quotes == 0)
			quotes = read[i];
		else if ((read[i]== '\'' || read[i] == '"') && (quotes == '"' || quotes == '\''))
			quotes = 0;
		i++;
	}
	if (quotes == 0)
		return (read);
	else
		return (get_those_quotes(read, quotes));
}

char	**ft_free(char **result)
{
	int	i;
	
	i = -1;
	while (result[++i])
		free(result[i]);
	free(result);
	return (0);
}