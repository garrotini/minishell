/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:52 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:53 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// extracts variable name after dollar sign,
// searchs in env value and replaces in string

static char	*process_var_expansion(char *s, int *i, t_env *env)
{
	char	*var_name;
	char	*value;
	int		var_len;

	var_len = get_var_len(s, *i + 1);
	var_name = malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (free(s), NULL);
	ft_strlcpy(var_name, s + *i + 1, var_len + 1);
	value = get_env_value(env, var_name);
	free(var_name);
	return (replace_var(s, i, value, var_len));
}

static char	*process_dollar(char *s, int *i, t_env *env, int exit_code)
{
	if (s[*i + 1] == '?')
		return (expand_exit_code(s, i, exit_code));
	if (!(s[*i + 1] == '_' || (s[*i + 1] >= 'a' && s[*i + 1] <= 'z')
			|| (s[*i + 1] >= 'A' && s[*i + 1] <= 'Z')))
		return ((*i)++, s);
	return (process_var_expansion(s, i, env));
}

// scans string for dollar signs,
// expands variable found
// marks expansion flag

static char	*expand_vars_in_str(char *s, t_env *env, int ec, int *exp)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '$')
		{
			s = process_dollar(s, &i, env, ec);
			if (!s)
				return (NULL);
			*exp = 1;
		}
		else
			i++;
	}
	return (s);
}

// returns false if token is single-quoted
// return true otherwise

static int	should_expand(char *str_bak)
{
	if (!str_bak || !*str_bak)
		return (1);
	if (str_bak[0] == '\'')
		return (0);
	return (1);
}

// iterates the tk list and expand variables
// at the end, if BIG_WORD token needs splitting 
// it apply_word_splitting() -> var_split.c

void	var_expansion(t_tk **tk_list, t_env *env, int exit_code)
{
	char	*temp;
	int		expanded;
	t_tk	*tk;
	t_tk	*next;

	tk = *tk_list;
	while (tk)
	{
		expanded = 0;
		next = tk->next;
		if (tk->type == WORD && should_expand(tk->str_bak))
		{
			temp = expand_vars_in_str(tk->str, env, exit_code, &expanded);
			if (!temp)
				return ;
			tk->str = temp;
		}
		tk->expand = expanded;
		if (needs_word_splitting(tk, expanded))
			apply_word_splitting(tk_list, &tk);
		tk = next;
	}
}
