/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_those_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:13:18 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/12 14:35:24 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_those_pipes(char *read)
{
	int		i;
	char	*new_read;
	char	*p;

	i = ft_strlen(read);
	while (i >= 0 && (read[i] <= 32 || read[i] >= 127))
	{
		i--;
	}
	if (read[i] == '|')
	{
		new_read = readline("> ");
		p = read;
		g_interactive = 1;
		read = ft_strjoin(read, new_read);
		g_interactive = 0;
		free(p);
		free(new_read);
		read = check_those_quotes(read);
		read = check_those_pipes(read);
	}
	return (read);
}