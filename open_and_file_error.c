/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_file_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:01:45 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/11 20:08:16 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_left(t_data *head, int i)
{
	int	fd;

	fd = open(head->files[i], O_RDWR | 0644);
	if (fd == -1)
		could_not_open(head->files[i]);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_open_right(t_data *head, int i)
{
	int	fd;

	fd = open(head->files[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		could_not_open(head->files[i]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_rightright(t_data *head, int i)
{
	int	fd;

	fd = open(head->files[i], O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
		could_not_open(head->files[i]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	could_not_open(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": could not open file or directory\n", 35);
}