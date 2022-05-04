/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/04 14:37:08 by pvillena         ###   ########.fr       */
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
	//t_data	*head;
	int		i;

	atexit(leaks);
	i = 0;
	while (1)
	{
		read = readline("minishell> ");
		read = check_those_quotes(read);
		cmds = ft_split_cmds(read, ' ');
		int i = 0;
		
		while (cmds[i])
			printf("cmds: %s\n", cmds[i++]);
		//head = parse_machine(cmds);
		if(*read)
			add_history(read);
		if (ft_strncmp(read, "exit", 100) == 0)
		{
			ft_free(cmds);
			exit(0);
		}
		/* while (cmds[i])
		{
			printf("Command: %s\n", cmds[i]);
			i++;
		} */
		i = 0;
		ft_free(cmds);
		free(read);
	}
	return (0);
}
