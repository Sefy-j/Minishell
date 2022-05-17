/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:14:45 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/17 19:53:56 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	no_ctrlprint(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	handler_ctrlc_child(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive == 1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		close(0);
		g_interactive = 3;
	}
	else
		ft_putstr_fd("^C\n", 1);
}

void	handler_ctrlc(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive == 1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		close(0);
		g_interactive = 3;
	}
}

void	handler_ctrlslash(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive)
	{
		rl_on_new_line();
		rl_redisplay();
		//printf("\b \b\b \b");
		return ;
	}
	printf("Quit\n");
}

void	signals_handlers_child(void)
{
	struct sigaction	ctrlc;

	ctrlc.sa_handler = &handler_ctrlc_child;
	sigaction(SIGINT, &ctrlc, NULL);
}

void	signals_handlers(void)
{
	struct sigaction	ctrlc;
	struct sigaction	ctrlslash;

	ctrlc.sa_handler = &handler_ctrlc;
	ctrlslash.sa_handler = &handler_ctrlslash;
	sigaction(SIGINT, &ctrlc, NULL);
	sigaction(SIGQUIT, &ctrlslash, NULL);
}
