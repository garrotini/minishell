/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:39:46 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:39:48 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// lexer has 5 stages:
// 1. validate_quotes()
// 2. split_input() // split.c
// 3. get_tk_list() // token.c
// 4. var_expansion() (might have var_split() as well)
// 5. rm_quote()

static int	validate_quotes(char *input)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (input[i])
	{
		if (!in_quote && (input[i] == '\'' || input[i] == '\"'))
			in_quote = input[i];
		else if (in_quote == '\"' && input[i] == '\\' && input[i + 1])
			i++;
		else if (in_quote && input[i] == in_quote)
			in_quote = 0;
		i++;
	}
	if (in_quote == '\'')
		return (perror_unclosed_quote('\''));
	if (in_quote == '\"')
		return (perror_unclosed_quote('\"'));
	return (0);
}

int	lexer(t_sh *sh)
{
	char	**av;

	if (!sh)
		return (0);
	if (!sh->input || all_spaces(sh->input))
		return (0);
	if (validate_quotes(sh->input))
		return (0);
	av = split_input(skip_spaces(sh->input) + sh->input);
	if (!av)
		return (0);
	sh->tk = get_tk_list(av);
	if (av)
		free_split(av);
	if (!sh->tk)
		return (0);
	var_expansion(&sh->tk, sh->env, sh->exit_code);
	if (!sh->tk)
		return (0);
	rm_quote(sh->tk);
	if (!sh->tk)
		return (0);
	return (1);
}
