/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:14:45 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/12 19:36:38 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	handler_ctrlc(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive == 1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		rl_replace_line("\r", 0);
		rl_on_new_line();
		printf("\n");
		g_interactive = 3;
	}
	else
		printf("\n");
}

void	handler_ctrlslash(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive)
	{
		printf("\b \b\b \b");
		return ;
	}
	printf("Quit\n");
}

void	signals_handlers()
{
	struct sigaction	ctrlc;
	struct sigaction	ctrlslash;

	ctrlc.sa_handler = &handler_ctrlc;
	ctrlslash.sa_handler = &handler_ctrlslash;
	sigaction(SIGINT, &ctrlc, NULL);
	sigaction(SIGQUIT, &ctrlslash, NULL);
}