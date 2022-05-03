/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_those_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:34:54 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/03 19:35:04 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_those_quotes(char *read, char quotes)
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