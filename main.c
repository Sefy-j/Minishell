/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/05 13:12:56 by pvillena         ###   ########.fr       */
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
	char	***cmds;
	char	**pipes;
	t_data	*head;
	t_data	*print;
	int		i;

	atexit(leaks);
	i = 0;
	while (1)
	{
		read = readline(GREEN"minishell> "RESET);
		read = check_those_quotes(read);
		pipes = split_pipes(read);
		// printf("--------------PIPES--------------------------------\n");
		// print_matrix(pipes);
		// printf("--------------PIPES--------------------------------\n");
		i = count_strs(pipes);
		cmds = malloc(sizeof(char ***) * (i + 1));
		pipes[i] = NULL;
		i = 0;
		while (pipes[i])
		{
			cmds[i] = ft_argvsplit(pipes[i]);
			i++;
		}
		i = 1;
		head = parse_machine(cmds[0]);
		while (pipes[i])
			ft_lstadd_back(&head, parse_machine(cmds[i++]));
		print = head;
		while (print)
		{
			print_struct(*print);
			printf("---------------------------\n");
			print = print->next;
		}
		if(*read)
			add_history(read);
		if (ft_strncmp(read, "exit", 100) == 0)
		{
			ft_free(*cmds);
			exit(0);
		}
		i = 0;
		ft_free(*cmds);
		free(read);
	}
	return (0);
}
