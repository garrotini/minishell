/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:42 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:43 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	tk_set_operator(t_tk **tk, char *s)
{
	if (*s == '|')
		tk_lstadd_back(tk, tk_lstnew(NULL, PIPE));
	else if (*s == ';')
		tk_lstadd_back(tk, tk_lstnew(NULL, SEMICOLON));
	else if (*s == '<')
	{
		if (*(s + 1) == '<')
			return (tk_lstadd_back(tk, tk_lstnew(NULL, HEREDOC)), 2);
		tk_lstadd_back(tk, tk_lstnew(NULL, INPUT));
	}
	else if (*s == '>')
	{
		if (*(s + 1) == '>')
			return (tk_lstadd_back(tk, tk_lstnew(NULL, APPEND)), 2);
		tk_lstadd_back(tk, tk_lstnew(NULL, OUTPUT));
	}
	return (1);
}

// process token, and helps assign them a type:
// WORD, PIPE, SEMICOLON, INPUT, etc etc

static void	process_token_str(t_tk **tk, char *str)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == ';'
			|| str[i] == '<' || str[i] == '>')
			i += tk_set_operator(tk, str + i);
		else
		{
			start = i;
			len = calc_word_len(str + i);
			i += len;
			if (len > 0)
				tk_lstadd_back(tk, tk_lstnew(ft_substr(str, start, len), WORD));
		}
	}
}

// tokenization, creates token list

t_tk	*get_tk_list(char **av)
{
	t_tk	*tk;

	tk = NULL;
	while (*av)
	{
		process_token_str(&tk, *av);
		av++;
	}
	return (tk);
}
