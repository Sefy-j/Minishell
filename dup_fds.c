/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:11:19 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/10 03:15:48 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_infile(t_data *head)
{
	int	i;
	int	last;

	i = -1;
	last = -1;
	while (head->dir[++i])
	{
		if (head->dir[i] == LEFT || head->dir[i] == LEFTLEFT)
			last = i;
	}
	return (last);
}

static int	get_outfile(t_data *head)
{
	int	i;
	int	last;

	i = -1;
	last = -1;
	while (head->dir[++i])
	{
		if (head->dir[i] == RIGHT || head->dir[i] == RIGHT)
			last = i;
	}
	return (last);
}

void	dup_fds(int pipe_fd[2], t_data *head)
{
	int	infile;
	int	outfile;
	int	fd;

	infile = -1;
	outfile = -1;
	fd = 0;
	if (head->files != NULL)
	{
		infile = get_infile(head);
		outfile = get_outfile(head);
		printf("my outfile: %d\n", outfile);
	}
	if (infile >= 0)
	{
		if (head->dir[infile] == LEFT)
		{
			fd = open(head->files[infile], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if (outfile >= 0)
	{
		if (head->dir[outfile] == RIGHT)
			fd = open(head->files[outfile], O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (head->dir[outfile] == RIGHTRIGHT)
			fd = open(head->files[outfile], O_CREAT | O_RDWR | O_APPEND);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (head->next != NULL)
		dup2(pipe_fd[1], STDOUT_FILENO);
}