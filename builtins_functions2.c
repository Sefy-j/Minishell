/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:27:58 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/09 11:20:00 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char **args, char **env)
{
	char	**new_env;
	int		i;
	int		j;
	int		flag;
	char	*p;

	i = -1;
	new_env = NULL;
	if (!env)
		return (new_env);
	while (env[++i])
	{
		flag = 1;
		j = -1;
		while (args[++j])
		{
			p = ft_strjoin(args[j], "=");
			if (ft_strncmp(env[i], p, ft_strlen(p)) == 0)
				flag = 0;
			free(p);
		}
		if (flag != 0)
			new_env = append_str(new_env, env[i]);
		else
			free(env[i]);
	}
	free(env);
	return (new_env);
}
