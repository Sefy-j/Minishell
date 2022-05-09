/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:27:58 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/09 18:59:11 by pvillena         ###   ########.fr       */
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
