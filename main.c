/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/09 14:28:39 by pvillena         ###   ########.fr       */
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

void	print_matrix_p(char **matrix)
{
	int i = 0;

	if (!matrix)
	{
		printf("Matrix: NULL\n");
		return;
	}
	printf("my matrix BIG: %p\n", matrix);
	while (matrix[i])
		printf("my matrix: %p\n", matrix[i++]);
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
	if (head.dir)
		printf("head dir: %s\n", head.dir);
}

void	leaks(void)
{
	system("leaks minishell");
}

t_data	*all_the_parsing_is_here(char *read)
{
	char	**cmds;
	//char	**pipes;
	t_data	*head;
	t_data	*print;
	int		i;

	read = check_those_quotes(read);
	cmds = ft_argvsplit(read);
	free(read);
	i = -1;
	print_matrix(cmds);
	print_matrix_p(cmds);
	head = parse_machine(cmds, &i);
	while(cmds[i])
		ft_lstadd_back(&head, parse_machine(cmds, &i));
	/* pipes = split_pipes(read);
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
	*/
	print = head;
	while (print)
	{
		print_struct(*print);
		printf("---------------------------\n");
		print = print->next;
	}
	free(cmds);
	return(head);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*read;
	t_data	*head;
	char	**env;

	if (argc != 1)
		return (0);
	if (argv[1])
		return (0);
	if (!envp)
		return (0);
	env = copy_matrix(envp);
	change_shlvl(env);
	atexit(leaks);
	while (1)
	{
		read = readline(GREEN"minishell> "RESET);
		if(*read)
			add_history(read);
		else
		{
			free(read);
			continue ;
		}
		head = all_the_parsing_is_here(read);
		// if (ft_strncmp(*head->cmds, "exit", 10) == 0)
		// {
		// 	printf("exit here\n");
		// 	exit(1);
		env = exec_builtins(head, env);
		ft_lstclear(&head);
	}
	return (0);
}
