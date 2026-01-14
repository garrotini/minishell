/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:10 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:11 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// skips over quoted sections during split
// spaces inside quotes get treated as literal characters
// to later create "BIG_WORD" tokens

static size_t	handle_embedded_quote(char *s, size_t i)
{
	char	quote;

	quote = s[i++];
	while (s[i] && s[i] != quote)
	{
		if (quote == '\"' && s[i] == '\\' && s[i + 1])
			i += 2;
		else
			i++;
	}
	if (s[i] == quote)
		i++;
	return (i);
}

static int	count_until_delimiter(char *s, char del, size_t i)
{
	while (s[i])
	{
		if (del == '\"' && s[i] == '\\' && s[i + 1])
			i += 2;
		else if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
			i = handle_embedded_quote(s, i);
		else if ((del == '\"' || del == '\'') && del == s[i])
		{
			if (del == ' ')
				return (i);
			return (i + 1);
		}
		else if (del == ' ' && ft_isspace(s[i]))
			return (i);
		else
			i++;
	}
	if (del != ' ')
		return (-2);
	return (i);
}

// Find token size from string considering quotes and delimiters
static int	fd_tk_size(char *s, size_t i)
{
	char	del;
	int		len;

	del = ' ';
	if (s[0] == '\'')
		del = '\'';
	else if (s[0] == '\"')
		del = '\"';
	if (del != ' ')
		i = 1;
	len = count_until_delimiter(s, del, i);
	if (len < 0)
		return (len);
	if (del != ' ' && s[len] && !ft_isspace(s[len]))
		len += count_until_delimiter(s + len, ' ', 0);
	return (len);
}

// Process tokens from input string
static char	**tokenize_input(char *input, char *tmp)
{
	char	**av;
	int		tk_len;

	(void)tmp;
	av = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		tk_len = fd_tk_size(input, 0);
		if (tk_len == -2 && (*input == '\'' || *input == '\"'))
			perror_unclosed_quote(*input);
		if (tk_len < 0)
			return (free_split(av), NULL);
		av = add_str(av, input, tk_len);
		if (!av)
			return (NULL);
		input += tk_len;
	}
	return (av);
}

// split input string into an array of tokens
char	**split_input(char *input)
{
	char	**av;
	char	*tmp;

	tmp = ft_strdup(input);
	if (!tmp)
		return (NULL);
	tmp = rm_dollar_quote(tmp);
	if (!tmp)
		return (NULL);
	av = tokenize_input(tmp, tmp);
	free(tmp);
	return (av);
}
