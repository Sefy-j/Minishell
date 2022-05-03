/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:09:01 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/03 20:57:49 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strs(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

char	**append_str(char **origin, char *append)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (count_strs(origin) + 2));
	i = -1;
	while (origin[++i])
		ret[i] = origin[i];
	if (!origin)
		i--;
	ret[++i] = append;
	ret[++i] = NULL;
	free(origin);
	return (ret);
}

t_data	*get_file(char **cmds, char dir, int *i, t_data *head)
{
	char	*p;

	p = head->dir;
	head->dir = ft_strjoin(head->dir, &dir);
	if (!cmds[*i][1])
		head->files = append_str(head->files, cmds[++(*i)]);
	else
		head->files = append_str(head->files, ft_substr(cmds[(*i)++], 1, 1000000000));
	if (p)
		free(p);
	return (head);
}

t_data	*parse_machine(char **cmds)
{
	t_data	*head;
	int		i;

	i = -1;
	head = ft_calloc(sizeof(t_data), 1);
	while (cmds[++i])
	{
		if (ft_strncmp(cmds[i], "<", 1) == 0)
			head = get_file(cmds, LEFT, &i, head);
		//if (ft_strncmp(cmds[i], "", 1) == 0)
	}
	return (head);
}