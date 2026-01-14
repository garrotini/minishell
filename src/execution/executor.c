/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:28 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:29 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child(t_sh *sh, t_cmd *cmd, int in_fd, int out_fd)
{
	if ((cmd->io_fds && cmd->io_fds->fd_in == -1 && cmd->io_fds->infile)
		|| (cmd->io_fds && cmd->io_fds->fd_out == -1 && cmd->io_fds->outfile))
		exit_child(sh, 1);
	if (!cmd->cmd)
		exit_child(sh, 0);
	if (cmd->io_fds && cmd->io_fds->fd_in != -1)
		in_fd = cmd->io_fds->fd_in;
	if (cmd->io_fds && cmd->io_fds->fd_out != -1)
		out_fd = cmd->io_fds->fd_out;
	if (in_fd != STDIN_FILENO && (dup2(in_fd, STDIN_FILENO), 1))
		close(in_fd);
	if (out_fd != STDOUT_FILENO && (dup2(out_fd, STDOUT_FILENO), 1))
		close(out_fd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->cmd))
		exit_child(sh, exec_builtin(sh, cmd, &sh->env));
	else
		exec_command(sh, cmd);
}

static int	exec_standalone_builtin(t_sh *sh, t_cmd *cmd)
{
	if (cmd->io_fds && cmd->io_fds->fd_in == -1 && cmd->io_fds->infile)
		return (1);
	if (cmd->io_fds && cmd->io_fds->fd_out == -1 && cmd->io_fds->outfile)
		return (1);
	if (!cmd->cmd)
		return (0);
	return (exec_builtin(sh, cmd, &sh->env));
}

int	executor(t_sh *sh)
{
	t_cmd	*cmd;
	t_cmd	*pipe_start;

	cmd = sh->cmd;
	while (cmd)
	{
		if (!cmd->pipe_out && (is_builtin(cmd->cmd) || !cmd->cmd))
		{
			sh->exit_code = exec_standalone_builtin(sh, cmd);
			cmd = cmd->next;
			continue ;
		}
		pipe_start = cmd;
		while (cmd && cmd->pipe_out)
			cmd = cmd->next;
		sh->exit_code = execute_pipeline(sh, pipe_start, cmd);
		if (cmd)
			cmd = cmd->next;
	}
	return (sh->exit_code);
}
