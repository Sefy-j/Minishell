/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:39:43 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/04 20:26:33 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_splitcopy(const char *str, char **result, int *i, int l)
{
	result[l][i[2]] = str[i[0]];
	i[0]++;
	i[2]++;
	return (i);
}

int	*ft_splitcopyspecial(const char *str, char **result, int *i, int l)
{
	if(ft_strchr(SPSIGN, str[*i]) && str[*i] != ' ' && str[*i] != '\0')
	{
		i = ft_splitcopy(str, result, i, l);
		if((str[*i] == '<' && str[*i - 1] == '<') || (str[*i] == '>' && str[*i - 1] == '>'))
			i = ft_splitcopy(str, result, i, l);
		return (i);
	}		
	while (!ft_strchr(SPSIGN, str[*i]) && str[*i] != '\0')
	{
		if (str[i[0]] == '\'' )
		{
			i[0]++;
			while (str[i[0]] != '\'' && str[i[0]] != '\0')
				i = ft_splitcopy(str, result, i, l);
			i[0]++;
		}
		else if (str[i[0]] == '\"' )
		{
			i[0]++;
			while (str[i[0]] != '\"' && str[i[0]] != '\0')
				i = ft_splitcopy(str, result, i, l);
			i[0]++;
		}
		else
			i = ft_splitcopy(str, result, i, l);
	}
	return (i);
}

char	**ft_free(char **result)
{
	int	i;

	i = -1;
	while (result[++i])
		free(result[i]);
	free(result);
	return (0);
}
