/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-f <jlopez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:14:45 by jlopez-f          #+#    #+#             */
/*   Updated: 2022/05/12 11:49:03 by jlopez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	handler_ctrlc(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
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