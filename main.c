/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/03 19:53:46 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char	*read;
	char	**cmds;
	int		i;

	atexit(leaks);
	i = 0;
	while (1)
	{
		read = readline("minishell> ");
		read = check_those_quotes(read);
		cmds = ft_argvsplit(read);
		if(*read)
			add_history(read);
		if (ft_strncmp(read, "exit", 100) == 0)
		{
			ft_free(cmds);
			exit(0);
		}
		while (cmds[i])
		{
			printf("Command: %s\n", cmds[i]);
			i++;
		}
		i = 0;
		ft_free(cmds);
		free(read);
	}
	return (0);
}
