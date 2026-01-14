/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:19:50 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/07 13:19:55 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// removes quotes, sets token_mode
// and processes backslash in DQ

static void	process_quoted_token(t_tk *tk)
{
	char	quote_type;
	char	*temp;

	quote_type = strip_quotes(tk);
	if (!quote_type)
		return ;
	if (quote_type == '\'')
		tk->mode = IN_SQ;
	else if (quote_type == '\"')
	{
		tk->mode = IN_DQ;
		temp = process_backslash_dq(tk->str, 0, 0);
		if (!temp)
			return (tk_lstclear(&tk));
		free(tk->str);
		tk->str = temp;
	}
}

static void	process_unquoted_token(t_tk *tk)
{
	char	*temp;

	temp = process_backslash(tk->str, 0, 0);
	if (!temp)
		return (tk_lstclear(&tk));
	free(tk->str);
	tk->str = temp;
}

static int	is_fully_quoted(char *str)
{
	size_t	len;

	if (!str || !str[0])
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '\'' || str[0] == '\"') && str[0] == str[len - 1])
		return (1);
	return (0);
}

// removes quotes from fully-quoted tokens
// and processes backslashes in unquoted BIG_WORD token.

void	rm_quote(t_tk *tk)
{
	while (tk)
	{
		if (tk->str && is_fully_quoted(tk->str))
			process_quoted_token(tk);
		else if (tk->str && tk->type == WORD)
			process_unquoted_token(tk);
		tk = tk->next;
	}
}
