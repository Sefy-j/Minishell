/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/05 13:30:19 by pvillena         ###   ########.fr       */
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

t_data	*all_the_parsing_is_here(char *read)
{
	char	***cmds;
	char	**pipes;
	t_data	*head;
	t_data	*print;
	int		i;

	read = check_those_quotes(read);
	pipes = split_pipes(read);
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
	return(head);
}

int	main(void)
{
	char	*read;
	t_data	*head;

	atexit(leaks);
	while (1)
	{
		read = readline(GREEN"minishell> "RESET);
		head = all_the_parsing_is_here(read);
		
		if(*read)
			add_history(read);
		if (ft_strncmp(read, "exit", 100) == 0)
			exit(0);
		free(read);
	}
	return (0);
}
