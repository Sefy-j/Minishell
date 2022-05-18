/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:27:58 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/18 20:10:42 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char **args, char **env)
{
	char	**new_env;
	int		i[2];
	int		flag;
	char	*p;

	i[0] = -1;
	new_env = NULL;
	if (!env)
		return (new_env);
	while (env[++i[0]])
	{
		flag = 1;
		i[1] = -1;
		while (args[++i[1]])
		{
			p = ft_strjoin(args[i[1]], "=");
			if (ft_strncmp(env[i[0]], p, ft_strlen(p)) == 0)
				flag = 0;
			free(p);
		}
		if (flag != 0)
			new_env = append_str(new_env, env[i[0]]);
	}
	ft_free(env);
	return (new_env);
}

int	ft_pwd(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(ft_substr(env[i], 4, UINT_MAX), 1);
			return (1);
		}
	}
	return (0);
}

int	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (1);
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 1;
	if (args[1] && args[1][0] == '-')
	{
		new_line = 0;
		while (args[1][++i])
		{
			if ('n' != args[1][i])
				new_line = 1;
		}
	}
	i = 1;
	if (new_line == 0)
		i = 2;
	if (!args[i])
		return (1);
	ft_putstr_fd(args[i++], 1);
	while (args[i])
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i++], 1);
	}
	if (new_line == 1)
		ft_putchar_fd('\n', 1);
	return (1);
}
