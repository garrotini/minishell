/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:31:43 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:31:45 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sigint(int signo)
{
	(void)signo;
	g_signal_exit_code = 130;
	write(1, "\n", 1);
	rl_on_new_line();
}

static void	handle_sigquit(int signo)
{
	(void)signo;
	g_signal_exit_code = 131;
	write(1, "Quit (core dumped)\n", 19);
	rl_on_new_line();
}

void	set_signals_off(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = handle_sigint;
	sa_quit.sa_handler = handle_sigquit;
	sigaction(SIGINT, &sa_int, 0);
	sigaction(SIGQUIT, &sa_quit, 0);
}

void	reset_prompt(int signo)
{
	(void)signo;
	g_signal_exit_code = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_on(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = reset_prompt;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, 0);
	sigaction(SIGQUIT, &sa_quit, 0);
}
