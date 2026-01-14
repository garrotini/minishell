/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:00 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:01 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_backslash_dq(char *str, int i, int j)
{
	char	*result;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			if (str[i + 1] == '\"' || str[i + 1] == '\\'
				|| str[i + 1] == '$' || str[i + 1] == '`'
				|| str[i + 1] == '\n')
			{
				result[j++] = str[i + 1];
				i += 2;
			}
			else
				result[j++] = str[i++];
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static void	process_quoted_str(char *str, char *result, int *i, int *j)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '\"' && str[*i] == '\\' && str[*i + 1])
			result[(*j)++] = str[++(*i)];
		else
			result[(*j)++] = str[*i];
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

char	*process_backslash(char *str, int i, int j)
{
	char	*result;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			result[j++] = str[i + 1];
			i += 2;
		}
		else if (str[i] == '\'' || str[i] == '\"')
			process_quoted_str(str, result, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	strip_quotes(t_tk *tk)
{
	char	*temp;
	size_t	len;
	char	quote_type;

	quote_type = tk->str[0];
	len = ft_strlen(tk->str);
	temp = malloc(sizeof(char) * (len - 1));
	if (!temp)
		return (tk_lstclear(&tk), 0);
	ft_strlcpy(temp, tk->str + 1, len - 1);
	free(tk->str);
	tk->str = temp;
	temp = malloc(sizeof(char) * (len - 1));
	if (!temp)
		return (tk_lstclear(&tk), 0);
	ft_strlcpy(temp, tk->str_bak + 1, len - 1);
	free(tk->str_bak);
	tk->str_bak = temp;
	return (quote_type);
}
