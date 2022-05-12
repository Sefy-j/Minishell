/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/12 15:08:40 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interactive = 0;

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
	t_data	*head;
	t_data	*temp;
	int		i;

	read = check_those_quotes(read);
	read = check_those_pipes(read);
	if(*read)
		add_history(read);
	cmds = ft_argvsplit(read);
	print_matrix(cmds);
	i = -1;
	while (cmds[++i])
	{
		if (cmds[i][0] == '|' && cmds[i + 1][0] == '|')
		{
			write(2, "syntax error\n", 13);
			free(cmds);
			return (NULL);
		}
		if ((cmds[i][0] == '<' || cmds[i][0] == '>')
			&& (cmds[i + 1][0] == '<' || cmds[i + 1][0] == '>'))
		{	
			write(2, "syntax error\n", 13);
			free(cmds);
			return (NULL);
		}
	}
	free(read);
	i = -1;
	head = parse_machine(cmds, &i);
	temp = head;
	while(cmds[i])
		ft_lstadd_back(&head, parse_machine(cmds, &i));
	ft_free(cmds);
	return(head);
}

int	is_env_builtin(t_data *head)
{
	if (ft_lstsize(head) > 1)
		return (0);
	else if (ft_strncmp(head->cmds[0], "cd", 10) == 0)
		return (1);
	else if (ft_strncmp(head->cmds[0], "export", 10) == 0)
		return (1);
	else if (ft_strncmp(head->cmds[0], "exit", 10) == 0)
		return (1);
	else if (ft_strncmp(head->cmds[0], "unset", 10) == 0)
		return (1);
	else
		return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*read;
	t_data	*head;
	char	**env;
	int		std[2];
	int		status;

	if (argc != 1 || argv[1] || !envp)
		return (0);
	env = copy_matrix(envp);
	change_shlvl(env);
	status = 0;
	signals_handlers();
	//atexit(leaks);
	while (1)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		g_interactive = 1;
		read = readline(GREEN"minishell> "RESET);
		g_interactive = 0;
		if (!read)
		{
			printf("exit\n");
			exit(1);
		}
		if (*read == 4)
		{
			printf("NOS FUIMOS");
			exit(1);
		}
		read = dollarsign(read, env, status);
		head = all_the_parsing_is_here(read);
		if (!head)
			continue ;
		if (head->cmds && is_env_builtin(head) == 1)
			env = env_builtins(head, env);
		else
			status = pipex(head, env);
		dup2(STDIN_FILENO, std[0]);
		dup2(STDOUT_FILENO, std[1]);
		ft_lstclear(&head);
	}
	return (0);
}
