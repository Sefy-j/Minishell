/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:38:27 by pvillena          #+#    #+#             */
/*   Updated: 2022/05/10 04:22:25 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_status(pid_t pid, int cmd_nbr)
{
	int	status;

	waitpid(pid, &status, 0);
	while (cmd_nbr-- > 0)
		wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WSTOPSIG(status));
}

static char	*get_path(char **envp, char *cmd1)
{
	char	**all_paths;
	char	*check_path;
	int		i;

	if (!*cmd1 || !cmd1)
		exit(1);
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	i = -1;
	if (access(cmd1, F_OK) == 0)
		return (cmd1);
	*envp = ft_substr(*envp, 5, INT_MAX);
	all_paths = ft_split(envp[++i], ':');
	cmd1 = ft_strjoin("/", cmd1);
	check_path = ft_strjoin(*all_paths, cmd1);
	while (access(check_path, F_OK) != 0 && all_paths[++i])
	{
		free(check_path);
		check_path = ft_strjoin(all_paths[i], cmd1);
	}
	free(cmd1);
	ft_free(all_paths);
	free(*envp);
	return (check_path);
}

static void	exec_cmds(t_data *temp, int pipe_fd[2], char ***env)
{
	int	i;

	i = -1;
	dup_fds(pipe_fd, temp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(get_path(*env, temp->cmds[0]), temp->cmds, *env) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

int	pipex(t_data *head, char ***env)
{
	int		pipe_fd[2];
	int		pid;
	t_data	*temp;

	temp = head;
	while (temp)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
		pid = fork();
		printf("post_fork pid: %d\n", pid);
		if (pid == 0)
			exec_cmds(temp, pipe_fd, env);
		if (temp->next != NULL)
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		temp = temp->next;
	}
	close(STDIN_FILENO);
	return (get_status(pid, ft_lstsize(head)));
}