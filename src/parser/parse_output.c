/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:59 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:33:01 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	clear_old_outfiles(t_io_fds *io)
{
	if (io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (0);
		free(io->outfile);
		close(io->fd_out);
	}
	return (1);
}

static void	open_outfile(t_io_fds *io, char *file, char c)
{
	if (!clear_old_outfiles(io))
		return ;
	io->outfile = ft_strdup(file);
	if (c == 't')
		io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (c == 'a')
		io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		perror_msg(io->outfile, strerror(errno), NULL);
}

void	parse_output(t_cmd **cmd_lst, t_tk **tk_lst, char c)
{
	t_tk	*tk;
	t_cmd	*cmd;

	tk = *tk_lst;
	cmd = cmd_lstget_end(*cmd_lst);
	init_io(cmd);
	tk = tk->next;
	if (!tk)
		return ;
	open_outfile(cmd->io_fds, tk->str, c);
	tk = tk->next;
	*tk_lst = tk;
}
