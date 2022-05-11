/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:29:26 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/11 20:05:11 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lenchar(char const *s, int c)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] != c && s[len])
		len++;
	return (len);
}

char	*get_pwd(char **env)
{
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_substr(env[i], 4, UINT_MAX);
			return (path);
		}
	}
	return (NULL);
}
