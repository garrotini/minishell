/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/07 13:22:49 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	needs_word_splitting(t_tk *tk, int expanded)
{
	int	i;

	if (!expanded)
		return (0);
	if (!tk->str)
		return (0);
	if (tk->str_bak && (tk->str_bak[0] == '\'' || tk->str_bak[0] == '\"'))
		return (0);
	i = 0;
	while (tk->str[i])
	{
		if (is_whitespace(tk->str[i]))
			return (1);
		i++;
	}
	return (0);
}

// counts words in strings, mallocs, fill and returns an av

char	**split_by_whitespace(char *s)
{
	char	**av;
	int		n;

	if (!s)
		return (NULL);
	n = count_words(s);
	if (!n)
		return (NULL);
	av = malloc_av(n);
	if (!av)
		return (NULL);
	fill_av(av, s, n);
	return (av);
}

// insert array of av as new WORD tokens into list

void	ins_split_tk(t_tk **tk_list, t_tk *ins_pos, char **av)
{
	t_tk	*new_tk;
	int		i;

	i = 0;
	while (av[i])
	{
		new_tk = tk_lstnew(av[i], WORD);
		if (!new_tk)
			return ;
		new_tk->expand = 0;
		if (ins_pos)
			ins_tk_after(ins_pos, new_tk);
		else
		{
			new_tk->next = *tk_list;
			if (*tk_list)
				(*tk_list)->prev = new_tk;
			*tk_list = new_tk;
		}
		ins_pos = new_tk;
		i++;
	}
}

// deals with "BIG_WORD" token 
// by splitting it into multiple tokens

void	apply_word_splitting(t_tk **tk_list, t_tk **cur)
{
	char	**av;

	av = split_by_whitespace((*cur)->str);
	if (!av)
	{
		rm_tk_from_list(tk_list, *cur);
		tk_lstdelone(*cur);
		*cur = NULL;
		return ;
	}
	finalize_split(tk_list, cur, av);
}
