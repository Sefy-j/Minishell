/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:31:04 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/05 21:23:13 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(char **env)
{
	char	*shlvl;
	char	*sub;
	int		nbr;

	while (ft_strncmp(*env, "SHLVL=", 6))
		env++;
	sub = ft_substr(*env, 6, UINT_MAX);
	nbr = ft_atoi(sub) + 1;
	free(sub);
	sub = ft_itoa(nbr);
	shlvl = ft_strjoin("SHLVL=", sub);
	free(sub);
	free(*env);
	*env = shlvl;
}

char	**copy_matrix(char **envp)
{
	char	**env;
	char	**ret;

	env = malloc(sizeof(char *) * (count_strs(envp) + 1));
	ret = env;
	while (*envp)
		*env++ = ft_strdup(*envp++);
	*env = NULL;
	return (ret);
}

char	**exec_builtins(t_data *head, char **env)
{
	if (ft_strncmp(head->cmds[0], "echo", 10) == 0)
		ft_echo(head->cmds);
	else if (ft_strncmp(head->cmds[0], "pwd", 10) == 0)
		ft_pwd(env);
	else if (ft_strncmp(head->cmds[0], "pwd", 10) == 0)
		ft_pwd(env);
	else if (ft_strncmp(head->cmds[0], "env", 10) == 0)
		print_matrix(env);
	else if (ft_strncmp(head->cmds[0], "export", 10) == 0)
		env = ft_export(head->cmds, env);
	else if (ft_strncmp(head->cmds[0], "unset", 10) == 0)
		env = ft_unset(head->cmds, env);
	else if (ft_strncmp(head->cmds[0], "exit", 10) == 0)
	{
		if (head)
			ft_lstclear(&head);
		if (env)
			ft_free(env);
		exit(0);
	}
	return (env);
}
