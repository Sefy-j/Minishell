/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:38 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/18 19:53:40 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interactive = 0;

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

char	**double_pipes_and_files(char **cmds)
{
	int	i;

	if (!cmds)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		if (cmds[i][0] == '|' && cmds[i + 1][0] == '|')
		{
			write(2, "syntax error\n", 13);
			free(cmds);
			return (NULL);
		}
		if (((cmds[i][0] == '<' || cmds[i][0] == '>')
			&& (cmds[i + 1] && (cmds[i + 1][0] == '<'
			|| cmds[i + 1][0] == '>'))))
		{	
			write(2, "missing files\n", 14);
			free(cmds);
			return (NULL);
		}
	}
	return (cmds);
}

t_data	*all_the_parsing_is_here(char *read, char **env, int status)
{
	char	**cmds;
	t_data	*head;
	t_data	*temp;
	int		i;

	read = check_those_quotes(read);
	read = check_those_pipes(read);
	if (*read)
		ft_add_history(read);
	read = dollarsign(read, env, status);
	cmds = ft_argvsplit(read);
	free(read);
	cmds = double_pipes_and_files(cmds);
	if (!cmds)
		return (NULL);
	i = -1;
	head = parse_machine(cmds, &i);
	temp = head;
	while (cmds[i])
		ft_lstadd_back(&head, parse_machine(cmds, &i));
	ft_free(cmds);
	return (head);
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
	no_ctrlprint();
	status = 0;
	signals_handlers();
	ft_read_history();
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
			write(1, "exit\n", 6);
			exit(1);
		}
		head = all_the_parsing_is_here(read, env, status);
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
