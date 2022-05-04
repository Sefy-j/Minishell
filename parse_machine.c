/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:35:05 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/04 19:09:22 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strs(char **arr)
{
	int	length;

	length = 0;
	if (!arr)
		return (length);
	while (arr[length])
		length++;
	return (length);
}

char	**append_str(char **origin, char *append)
{
	char	**ret;
	int		i;

	print_matrix(origin);
	ret = (char **)malloc(sizeof(char *) * (count_strs(origin) + 2));
	i = 0;
	if (origin)
	{
		while (origin && origin[i])
		{
			ret[i] = origin[i];
			i++;
		}
	}
	ret[i] = append;
	ret[++i] = NULL;
	return (ret);
}

t_data	*get_file(char **cmds, char dir, int *i, t_data *head)
{
	char	*p;
	char	str[2];

	p = head->dir;
	str[0] = dir;
	str[1] = '\0';
	head->dir = ft_strjoin(head->dir, str);
	if ((dir == RIGHTRIGHT || dir == LEFTLEFT) && !cmds[*i][2])
		head->files = append_str(head->files, cmds[++(*i)]);
	else if (!cmds[*i][1])
		head->files = append_str(head->files, cmds[++(*i)]);
	else
	{
		if (dir == RIGHTRIGHT || dir == LEFTLEFT)
			head->files = append_str(head->files,
					ft_substr(cmds[*i], 2, ft_strlen(cmds[*i])));
		else
			head->files = append_str(head->files,
					ft_substr(cmds[*i], 1, ft_strlen(cmds[*i])));
	}
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
		if (ft_strncmp(cmds[i], ">>", 2) == 0)
			head = get_file(cmds, RIGHTRIGHT, &i, head);
		else if (ft_strncmp(cmds[i], "<<", 2) == 0)
			head = get_file(cmds, LEFTLEFT, &i, head);
		else if (ft_strncmp(cmds[i], "<", 1) == 0)
			head = get_file(cmds, LEFT, &i, head);
		else if (ft_strncmp(cmds[i], ">", 1) == 0)
			head = get_file(cmds, RIGHT, &i, head);
		else
			head->cmds = append_str(head->cmds, cmds[i]);
		print_matrix(head->cmds);
	}
	return (head);
}
