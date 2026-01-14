/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:48:01 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:48:02 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_init(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->path = NULL;
	(*cmd)->av = NULL;
	(*cmd)->av_mode = NULL;
	(*cmd)->pipe_out = 0;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*neo;

	neo = malloc(sizeof(t_cmd));
	if (!neo)
		return (NULL);
	ft_memset(neo, 0, sizeof(t_cmd));
	cmd_init(&neo);
	return (neo);
}

static void	free_cmd_av(t_cmd *cmd)
{
	int	i;

	if (cmd->av)
	{
		i = 0;
		while (cmd->av[i])
		{
			free(cmd->av[i]);
			i++;
		}
		free(cmd->av);
	}
	if (cmd->av_mode)
		free(cmd->av_mode);
}

void	free_cmd_io_fds(t_cmd *cmd)
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
		if (cmd->io_fds->infile)
			free(cmd->io_fds->infile);
		if (cmd->io_fds->outfile)
			free(cmd->io_fds->outfile);
		if (cmd->io_fds->heredoc_del)
			free(cmd->io_fds->heredoc_del);
		free(cmd->io_fds);
	}
}

void	cmd_lstdelone(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	free_cmd_av(cmd);
	if (cmd->pipe_fd)
		free(cmd->pipe_fd);
	free_cmd_io_fds(cmd);
	free(cmd);
}
