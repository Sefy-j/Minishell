/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_those_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:13:18 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/24 18:37:02 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_first_pipe(char *read)
{
	int		i;

	if (!read)
		return (ft_strdup(""));
	if (!*read)
		return (read);
	i = 0;
	while (read[i] && read[i] == 32)
		i++;
	if (read[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		ft_add_history(read);
		free(read);
		return (ft_strdup(""));
	}
	return (read);
}

char	*check_those_pipes(char *read)
{
	int		i;
	char	*new_read;
	char	*p;

	if (!read)
		return (ft_strdup(""));
	if (!*read)
		return (read);
	i = ft_strlen(read);
	while (i > 0 && (read[i] <= 32 || read[i] >= 127))
		i--;
	if (read && read[i] && read[i] == '|')
	{
		g_interactive = 2;
		new_read = readline("> ");
		if (!new_read || g_interactive == 3)
		{
			ft_add_history(read);
			free(read);
			free(new_read);
			g_interactive = 0;
			return (ft_strdup(""));
		}
		g_interactive = 0;
		p = read;
		read = ft_strjoin(read, new_read);
		free(p);
		free(new_read);
		read = check_those_quotes(read);
		read = check_those_pipes(read);
	}
	return (read);
}
