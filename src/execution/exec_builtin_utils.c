/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:21 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:36:53 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_redirections(t_cmd *cmd, int *stdin_bak, int *stdout_bak)
{
	if (cmd->io_fds && cmd->io_fds->fd_in != -1)
	{
		*stdin_bak = dup(STDIN_FILENO);
		dup2(cmd->io_fds->fd_in, STDIN_FILENO);
		close(cmd->io_fds->fd_in);
		cmd->io_fds->fd_in = -1;
	}
	if (cmd->io_fds && cmd->io_fds->fd_out != -1)
	{
		*stdout_bak = dup(STDOUT_FILENO);
		dup2(cmd->io_fds->fd_out, STDOUT_FILENO);
		close(cmd->io_fds->fd_out);
		cmd->io_fds->fd_out = -1;
	}
}

static void	restore_redirections(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}
// was static before but line too long

int	exec_builtin_cmd(char *cmd, char **av, t_tk_mode *av_mode, t_env **env)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(av, av_mode, env));
	else if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(av, env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(av));
	else if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(av, *env));
	else if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(av, env));
	else if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(av, env));
	else if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(av, env));
	else
		return (cmd_not_found(cmd));
}

int	exec_builtin(t_sh *sh, t_cmd *cmd, t_env **env)
{
	int	ret;
	int	stdin_backup;
	int	stdout_backup;

	(void)sh;
	stdin_backup = -1;
	stdout_backup = -1;
	setup_redirections(cmd, &stdin_backup, &stdout_backup);
	ret = exec_builtin_cmd(cmd->cmd, cmd->av, cmd->av_mode, env);
	restore_redirections(stdin_backup, stdout_backup);
	return (ret);
}
