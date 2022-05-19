/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_those_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:26:43 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/18 19:57:03 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_those_quotes(char *read, char quotes)
{
	char	*new_read;
	char	*p;
	char	*q;

	p = read;
	read = ft_strjoin(read, "\n");
	free(p);
	g_interactive = 2;
	new_read = readline("> ");
	if (!new_read || g_interactive == 3)
	{
		p = ft_substr(read, 0, ft_strlen(read) - 1);
		ft_add_history(p);
		free(p);
		free(read);
		free(new_read);
		g_interactive = 0;
		return (ft_strdup(""));
	}
	g_interactive = 0;
	while (read && !ft_strchr(new_read, (int)quotes))
	{
		p = new_read;
		new_read = ft_strjoin(new_read, "\n");
		free(p);
		g_interactive = 2;
		q = readline("> ");
		if (!q || g_interactive == 3)
		{
			free(q);
			q = ft_strjoin(read, new_read);
			p = ft_substr(q, 0, ft_strlen(q) - 1);
			ft_add_history(p);
			free(p);
			free(read);
			free(new_read);
			free(q);
			g_interactive = 0;
			return (ft_strdup(""));
		}
		g_interactive = 0;
		p = new_read;
		new_read = ft_strjoin(p, q);
		free(q);
		free(p);
	}
	p = read;
	read = ft_strjoin(read, new_read);
	free(new_read);
	free(p);
	check_those_quotes(read);
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
		if ((read[i] == '\'' || read[i] == '"') && quotes == 0)
			quotes = read[i];
		else if ((read[i] == '\'' || read[i] == '"') && quotes == read[i])
			quotes = 0;
		i++;
	}
	if (quotes == 0)
		return (read);
	else
		return (get_those_quotes(read, quotes));
}
