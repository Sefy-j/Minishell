/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/04 17:56:59 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_matrix(char **matrix)
{
	int i = 0;

	if (!matrix)
	{
		printf("Matrix: NULL\n");
		return;
	}
	while (matrix[i])
		printf("my matrix: %s\n", matrix[i++]);
}

void	print_struct(t_data head)
{
	int	i;

	i = -1;
	if (head.cmds)
	{
		while (head.cmds[++i])
			printf("head cmds: %s\n", head.cmds[i]);
	}
	i = -1;
	if (head.files)
	{
		while (head.files[++i])
			printf("head files: %s\n", head.files[i]);
	}
	printf("head dir: %s\n", head.dir);
}

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char	*read;
	char	**cmds;
	t_data	*head;
	int		i;

	atexit(leaks);
	i = 0;
	while (1)
	{
		read = readline("minishell> ");
		read = check_those_quotes(read);
		cmds = ft_argvsplit(read);
		while (cmds[i])
			printf("cmds: %s\n", cmds[i++]);
		head = parse_machine(cmds);
		print_struct(*head);
		if(*read)
			add_history(read);
		if (ft_strncmp(read, "exit", 100) == 0)
		{
			ft_free(cmds);
			exit(0);
		}
		i = 0;
		ft_free(cmds);
		free(read);
	}
	return (0);
}
