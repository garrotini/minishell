/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:33:32 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:33:34 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cmd_get(t_tk **tk_lst, t_tk_mode *mode)
{
	char	*cmd;

	cmd = NULL;
	if (*tk_lst && (*tk_lst)->type == WORD)
	{
		cmd = ft_strdup((*tk_lst)->str);
		if (mode)
			*mode = (*tk_lst)->mode;
		*tk_lst = (*tk_lst)->next;
	}
	return (cmd);
}

static int	cmd_build(t_cmd **cmd, t_tk_mode mode)
{
	(*cmd)->av = malloc(sizeof(*cmd)->av * 2);
	if (!(*cmd)->av)
		return (0);
	(*cmd)->av_mode = malloc(sizeof(t_tk_mode) * 2);
	if (!(*cmd)->av_mode)
		return (free((*cmd)->av), 0);
	(*cmd)->av[0] = ft_strdup((*cmd)->cmd);
	(*cmd)->av[1] = NULL;
	(*cmd)->av_mode[0] = mode;
	(*cmd)->av_mode[1] = UNQUOTED;
	return (1);
}

void	parse_word(t_cmd **cmd_lst, t_tk **tk_lst)
{
	t_cmd		*cmd_temp;
	t_tk		*tk_temp;
	t_tk_mode	mode;

	tk_temp = *tk_lst;
	while (tk_temp && tk_temp->type == WORD)
	{
		cmd_temp = cmd_lstget_end(*cmd_lst);
		if (!cmd_temp->cmd || (tk_temp->prev && tk_temp->prev->type == PIPE))
		{
			cmd_temp->cmd = cmd_get(&tk_temp, &mode);
			if (!cmd_temp->av)
			{
				if (!cmd_build(&cmd_temp, mode))
					return ;
			}
		}
		if (tk_temp && tk_temp->type == WORD)
			cmd_fill_av(&tk_temp, cmd_temp);
	}
	*tk_lst = tk_temp;
}
