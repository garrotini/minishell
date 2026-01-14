/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:23 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:24 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fork_and_exec_cmd(t_sh *sh, t_cmd *cmd, int in_fd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe_out)
			close(fd[0]);
		exec_child(sh, cmd, in_fd, fd[1]);
	}
	else if (pid < 0)
		return (perror("minishell: fork failed"), -1);
	return (0);
}

static int	wait_for_children(void)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			last_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
		}
	}
	return (last_status);
}

static int	handle_pipe_fd(t_cmd *cmd, int fd[2])
{
	if (cmd->pipe_out && pipe(fd) == -1)
		return (perror("minishell: pipe failed"), -1);
	if (!cmd->pipe_out)
		fd[1] = STDOUT_FILENO;
	return (0);
}

static void	update_pipe_fd(t_cmd *cmd, int *in_fd, int fd[2])
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cmd->pipe_out && (close(fd[1]), 1))
		*in_fd = fd[0];
	else
		*in_fd = STDIN_FILENO;
}

int	execute_pipeline(t_sh *sh, t_cmd *start, t_cmd *end)
{
	t_cmd	*cmd;
	int		in_fd;
	int		fd[2];
	int		exit_code;

	cmd = start;
	in_fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd && cmd != end->next)
	{
		if (handle_pipe_fd(cmd, fd) == -1)
			return (1);
		if (fork_and_exec_cmd(sh, cmd, in_fd, fd) == -1)
			return (1);
		update_pipe_fd(cmd, &in_fd, fd);
		cmd = cmd->next;
	}
	exit_code = wait_for_children();
	set_signals_off();
	return (exit_code);
}
