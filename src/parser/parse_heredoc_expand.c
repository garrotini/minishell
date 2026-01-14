/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:50:22 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/08 01:50:30 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_heredoc_var(char *s, int *i, t_env *env, int exit_code)
{
	char	*var_name;
	char	*value;
	int		var_len;
	char	*result;

	if (s[*i + 1] == '?')
	{
		var_name = ft_itoa(exit_code);
		var_len = 1;
	}
	else
	{
		var_len = get_var_len(s, *i + 1);
		var_name = malloc(sizeof(char) * (var_len + 1));
		if (!var_name)
			return (free(s), NULL);
		ft_strlcpy(var_name, s + *i + 1, var_len + 1);
		value = get_env_value(env, var_name);
		free(var_name);
		var_name = value;
	}
	result = replace_var(s, i, var_name, var_len);
	if (s[*i + 1] == '?')
		free(var_name);
	return (result);
}

char	*expand_heredoc_line(char *line, t_env *env, int exit_code)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '_'
				|| (line[i + 1] >= 'a' && line[i + 1] <= 'z')
				|| (line[i + 1] >= 'A' && line[i + 1] <= 'Z')
				|| line[i + 1] == '?'))
		{
			line = expand_heredoc_var(line, &i, env, exit_code);
			if (!line)
				return (NULL);
		}
		else
			i++;
	}
	return (line);
}
