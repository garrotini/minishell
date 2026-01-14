/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:45 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:32:47 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	clear_old_infiles(t_io_fds *io)
{
	if (io->infile)
	{
		if (io->fd_in < 0 || (io->outfile && io->fd_out < 0))
			return (0);
		free(io->infile);
		close (io->fd_in);
	}
	return (1);
}

static void	open_infile(t_io_fds *io, char *file)
{
	if (!clear_old_infiles(io))
		return ;
	io->infile = ft_strdup(file);
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in < 0)
		perror_msg(io->infile, strerror(errno), NULL);
}

void	parse_input(t_cmd **cmd_lst, t_tk **tk_lst)
{
	t_tk	*tk;
	t_cmd	*cmd;

	tk = *tk_lst;
	cmd = cmd_lstget_end(*cmd_lst);
	init_io(cmd);
	tk = tk->next;
	if (!tk)
		return ;
	open_infile(cmd->io_fds, tk->str);
	tk = tk->next;
	*tk_lst = tk;
}
