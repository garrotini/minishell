/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:30 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:32:35 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creates unique temp filename for heredocs
// based on /tmp/minishell_heredoc_n

static void	heredoc_setup_file(t_io_fds *io, int *i)
{
	char	*n;

	n = ft_itoa((*i)++);
	if (!n)
		return ;
	io->infile = ft_strjoin(HEREDOC_NAME, n);
	free(n);
}

// it always clears old heredoc(or input, or output)!
// sets delimiter, creates temp file, opens for reading

void	parse_heredoc(t_sh *sh, t_tk **tk_lst)
{
	t_cmd		*cmd;
	t_io_fds	*io;
	static int	i;

	cmd = cmd_lstget_end(sh->cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!heredoc_clear(io))
		return ;
	*tk_lst = (*tk_lst)->next;
	if (io->heredoc_del)
		free(io->heredoc_del);
	io->heredoc_del = ft_strdup((*tk_lst)->str);
	if ((*tk_lst)->mode == IN_SQ || (*tk_lst)->mode == IN_DQ)
		io->heredoc_expand = 0;
	heredoc_setup_file(io, &i);
	if (heredoc_create(io, sh))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	*tk_lst = (*tk_lst)->next;
}
