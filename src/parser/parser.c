/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:33:58 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:34:00 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_token(t_sh *sh, t_tk **temp)
{
	if ((*temp)->type == WORD)
		parse_word(&sh->cmd, temp);
	else if ((*temp)->type == PIPE)
		parse_pipe(&sh->cmd, temp);
	else if ((*temp)->type == SEMICOLON)
		parse_semicolon(&sh->cmd, temp);
	else if ((*temp)->type == INPUT)
		parse_input(&sh->cmd, temp);
	else if ((*temp)->type == OUTPUT)
		parse_output(&sh->cmd, temp, 't');
	else if ((*temp)->type == APPEND)
		parse_output(&sh->cmd, temp, 'a');
	else if ((*temp)->type == HEREDOC)
		parse_heredoc(sh, temp);
	else if ((*temp)->type != END)
		*temp = (*temp)->next;
}

void	parser(t_sh *sh)
{
	t_tk	*temp;

	temp = sh->tk;
	while (temp && temp->type != END)
	{
		if (temp == sh->tk)
			cmd_lstadd_end(&sh->cmd, cmd_lstnew());
		parse_token(sh, &temp);
	}
}
