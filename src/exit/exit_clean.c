/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:24 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:30:25 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->io_fds)
		{
			if (cmd->io_fds->fd_in >= 0)
				close(cmd->io_fds->fd_in);
			if (cmd->io_fds->fd_out >= 0)
				close(cmd->io_fds->fd_out);
			if (cmd->io_fds->stdin_bak >= 0)
				close(cmd->io_fds->stdin_bak);
			if (cmd->io_fds->stdout_bak >= 0)
				close(cmd->io_fds->stdout_bak);
		}
		cmd = cmd->next;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_sh(t_sh *sh)
{
	if (sh->input)
	{
		free(sh->input);
		sh->input = NULL;
	}
	if (sh->tk)
		tk_lstclear(&sh->tk);
	if (sh->cmd)
		cmd_lstclear(&sh->cmd);
}

void	full_clean(t_sh *sh)
{
	if (!sh)
		return ;
	close_fds(sh->cmd);
	free_sh(sh);
	free_env_list(sh->env);
	rl_clear_history();
}

void	exit_sh(t_sh *sh)
{
	int	exit_code;

	exit_code = 0;
	if (sh)
		exit_code = sh->exit_code;
	full_clean(sh);
	exit(exit_code);
}
