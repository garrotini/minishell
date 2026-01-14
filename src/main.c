/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:30:44 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:30:47 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_exit_code = 0;

static void	process_command(t_sh *sh)
{
	if (lexer(sh))
	{
		add_history(sh->input);
		tk_lstadd_back(&sh->tk, tk_lstnew(NULL, END));
		if (syntaxer(&sh->tk))
			sh->exit_code = 2;
		else
		{
			parser(sh);
			sh->exit_code = executor(sh);
		}
	}
	free_sh(sh);
}

// main REPL (read, eval, print loop)

void	shell_loop(t_sh *sh)
{
	while (1)
	{
		set_signals_on();
		sh->input = readline(PS1);
		set_signals_off();
		if (g_signal_exit_code != 0)
		{
			sh->exit_code = g_signal_exit_code;
			g_signal_exit_code = 0;
		}
		if (!sh->input)
		{
			fd_putstr(1, "exit", 1);
			sh->exit_code = 0;
			rl_clear_history();
			exit_sh(sh);
		}
		process_command(sh);
	}
}

int	main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void)av;
	if (ac != 1)
	{
		fd_putstr(2, "Invalid call to minishell program", 1);
		return (EXIT_FAILURE);
	}
	if (!init_shell(&sh, env))
		exit_sh(&sh);
	shell_loop(&sh);
	exit_sh(&sh);
	return (0);
}
