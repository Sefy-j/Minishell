/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:11:19 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/11 19:37:37 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_writeheredoc(char *limiter, int *pfd)
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
void	ft_readheredoc(t_data *head, int i)
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

void	could_not_open(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": could not open file or directory\n", 35);
}

void	dup_fds(int pipe_fd[2], t_data *head)
{
	int	fd;
	int	outfile;
	int	i;

	outfile = 0;
	i = -1;
	fd = 0;
	while (head->files && head->files[++i])
	{
		if (head->dir[i] == LEFT)
		{
			fd = open(head->files[i], O_RDWR | 0644);
			if (fd == -1)
				could_not_open(head->files[i]);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (head->dir[i] == LEFTLEFT)
			ft_readheredoc(head, i);
		else if (head->dir[i] == RIGHT)
		{
			fd = open(head->files[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				could_not_open(head->files[i]);
			outfile = 1;
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (head->dir[i] == RIGHTRIGHT)
		{
			fd = open(head->files[i], O_CREAT | O_RDWR | O_APPEND);
			if (fd == -1)
				could_not_open(head->files[i]);
			outfile = 1;
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	if (head->next != NULL && outfile == 0)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else if (outfile == 0)
		dup2(head->std[1], STDOUT_FILENO);
}
