/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:49:19 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/05 19:40:22 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		return ;
	if (ft_strncmp(args[1], "-n", 10) == 0)
		i = 2;
	else
		i = 1;
	if (!args[i])
		return ;
	printf("%s", args[i++]);
	while (args[i])
		printf(" %s", args[i++]);
	if (ft_strncmp(args[1], "-n", 10) == 0)
		return ;
	printf("\n");
}

void	ft_pwd(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", ft_substr(env[i], 4, UINT_MAX));
			return ;
		}
	}
}

static char	**input_var(char **env, char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = malloc(sizeof(char *) * (count_strs(env) + 2));
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(str);
	new_env[++i] = NULL;
	ft_free(env);
	return (new_env);
}

static int	check_var(char *str)
{
	if (!ft_strchr(str, '='))
		return (0);
	if (ft_isalpha(*str) == 0 && *str != '_')
		return (0);
	while (*str != '=')
	{
		if (*str != '_' && ft_isalnum(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

char	**ft_export(char **args, char **env)
{
	int		i;
	int		flag;

	i = 0;
	while (args[++i])
	{
		flag = check_var(args[i]);
		if (flag)
			env = input_var(env, args[i]);
	}
	return (env);
}