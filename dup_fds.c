/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:11:19 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/11 20:10:47 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_writeheredoc(char *limiter, int *pfd)
{
	size_t	len;
	char	*line;

	len = ft_strlen(limiter);
	while (limiter)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			close(pfd[0]);
			close(pfd[1]);
			exit(1);
		}
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			close(pfd[0]);
			close(pfd[1]);
			exit(0);
		}
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}

static void	ft_readheredoc(t_data *head, int i)
{
	int		pfd[2];
	pid_t	pid;

	dup2(head->std[0], STDIN_FILENO);
	if (pipe(pfd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		ft_writeheredoc(head->files[i], pfd);
	}
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	wait(NULL);
}

void	dup_fds(int pipe_fd[2], t_data *head)
{
	int	i;

	i = -1;
	while (head->files && head->files[++i])
	{
		if (head->dir[i] == LEFT)
			ft_open_left(head, i);
		else if (head->dir[i] == LEFTLEFT)
			ft_readheredoc(head, i);
		else if (head->dir[i] == RIGHT)
			ft_open_right(head, i);
		else if (head->dir[i] == RIGHTRIGHT)
			ft_open_rightright(head, i);
	}
	if (head->next != NULL && (!ft_strchr(head->dir, RIGHT)
			&& !ft_strchr(head->dir, RIGHTRIGHT)))
		dup2(pipe_fd[1], STDOUT_FILENO);
	else if (!ft_strchr(head->dir, RIGHT)
		&& !ft_strchr(head->dir, RIGHTRIGHT))
		dup2(head->std[1], STDOUT_FILENO);
}
