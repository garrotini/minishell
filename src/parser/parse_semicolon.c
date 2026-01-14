/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:33:22 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:33:23 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_semicolon(t_cmd **cmd_lst, t_tk **tk_lst)
{
	t_cmd	*last_cmd;

	last_cmd = cmd_lstget_end(*cmd_lst);
	cmd_lstadd_end(&last_cmd, cmd_lstnew());
	*tk_lst = (*tk_lst)->next;
}
