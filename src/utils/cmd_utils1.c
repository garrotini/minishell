/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:47:53 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:47:54 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_lstadd_end(t_cmd **lst, t_cmd *cmd)
{
	t_cmd	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = cmd;
		return ;
	}
	if (lst && *lst && cmd)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = cmd;
		cmd->prev = temp;
	}
}

t_cmd	*cmd_lstget_end(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	cmd_lstclear(t_cmd **lst)
{
	t_cmd	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		cmd_lstdelone(*lst);
		*lst = NULL;
		*lst = temp;
	}
}
