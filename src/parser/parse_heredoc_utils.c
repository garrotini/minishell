/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:19:13 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/06 17:19:16 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_clear(t_io_fds *io)
{
	if (io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (0);
		if (io->heredoc_del != NULL)
		{
			free(io->heredoc_del);
			io->heredoc_del = NULL;
		}
		free(io->infile);
		close(io->fd_in);
	}
	return (1);
}

static int	write_heredoc_line(int fd, char *line, t_io_fds *io, t_sh *sh)
{
	char	*expanded;

	if (io->heredoc_expand)
	{
		expanded = expand_heredoc_line(line, sh->env, sh->exit_code);
		if (!expanded)
			return (-2);
		fd_putstr(fd, expanded, 1);
		free(expanded);
	}
	else
	{
		fd_putstr(fd, line, 1);
		free(line);
	}
	return (-1);
}

static int	process_heredoc_line(char *line, int fd, t_io_fds *io, t_sh *sh)
{
	if (!line)
	{
		if (g_signal_exit_code != 0)
			return (-2);
		printf(HEREDOC_ERROR1);
		printf("1 ");
		printf(HEREDOC_ERROR2);
		printf("(wanted '%s')\n", io->heredoc_del);
		return (0);
	}
	if (!ft_strncmp(line, io->heredoc_del, ft_strlen(io->heredoc_del) + 1))
		return (free(line), 1);
	return (write_heredoc_line(fd, line, io, sh));
}

int	heredoc_fill(t_io_fds *io, int fd, t_sh *sh)
{
	char	*line;
	int		ret;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	while (1)
	{
		set_signals_heredoc();
		line = readline(">");
		set_signals_off();
		if (g_signal_exit_code != 0)
		{
			if (line)
				free(line);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			return (-2);
		}
		ret = process_heredoc_line(line, fd, io, sh);
		if (ret == -2)
			return (-2);
		if (ret != -1)
			return (close(stdin_backup), ret);
	}
}

int	heredoc_create(t_io_fds *io, t_sh *sh)
{
	int	fd_temp;
	int	ret;

	ret = 1;
	fd_temp = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = heredoc_fill(io, fd_temp, sh);
	close(fd_temp);
	if (ret == -2)
	{
		unlink(io->infile);
		return (0);
	}
	return (ret);
}
