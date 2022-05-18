/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_those_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:13:18 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/18 19:51:26 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_those_pipes(char *read)
{
	int		i;
	char	*new_read;
	char	*p;

	if (!read || !*read)
		return (ft_strdup(""));
	i = ft_strlen(read);
	while (i >= 0 && (read[i] <= 32 || read[i] >= 127))
	{
		i--;
	}
	if (read[i] == '|')
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
