/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_split_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/07 13:20:27 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	count_words(char *s)
{
	int	n;
	int	in_word;
	int	i;

	n = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		if (is_whitespace(s[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			n++;
		}
		i++;
	}
	return (n);
}

char	*extract_word(char *str, int *pos)
{
	int		start;
	int		len;
	char	*word;

	while (str[*pos] && is_whitespace(str[*pos]))
		(*pos)++;
	start = *pos;
	len = 0;
	while (str[*pos] && !is_whitespace(str[*pos]))
	{
		(*pos)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str + start, len + 1);
	return (word);
}

static t_tk	*get_last_ins(t_tk *start, int count)
{
	int	i;

	i = 0;
	while (i < count && start)
	{
		start = start->next;
		i++;
	}
	return (start->prev);
}

void	finalize_split(t_tk **tk_list, t_tk **cur, char **av)
{
	t_tk	*ins_pos;
	t_tk	*to_delete;
	int		av_count;

	ins_pos = (*cur)->prev;
	ins_split_tk(tk_list, ins_pos, av);
	av_count = count_av(av);
	if (ins_pos)
		*cur = get_last_ins(ins_pos->next, av_count);
	else
		*cur = get_last_ins(*tk_list, av_count);
	to_delete = (*cur)->next;
	rm_tk_from_list(tk_list, to_delete);
	tk_lstdelone(to_delete);
	free(av);
}
