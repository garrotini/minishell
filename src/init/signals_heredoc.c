/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:15:18 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/06 17:15:23 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint(int signo)
{
	(void)signo;
	g_signal_exit_code = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = heredoc_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, 0);
	sigaction(SIGQUIT, &sa_quit, 0);
}
