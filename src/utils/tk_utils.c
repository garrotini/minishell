/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:49:21 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:49:22 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tk_lstadd_back(t_tk **lst, t_tk *tk)
{
	t_tk	*temp;

	if (!tk || !lst)
		return ;
	if (!*lst)
	{
		*lst = tk;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = tk;
	tk->prev = temp;
}

t_tk	*tk_lstnew(char *str, int type)
{
	t_tk	*new;
	char	*str_bak;

	new = malloc(sizeof(t_tk));
	if (!new)
		return (NULL);
	new->str = NULL;
	if (str)
	{
		str_bak = ft_strdup(str);
		if (!str_bak)
			return (tk_lstdelone(new), NULL);
	}
	else
		str_bak = NULL;
	new->str = str;
	new->str_bak = str_bak;
	new->type = type;
	new->mode = UNQUOTED;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	tk_lstdelone(t_tk *tk)
{
	if (!tk)
		return ;
	if (tk->str)
		free(tk->str);
	if (tk->str_bak)
		free(tk->str_bak);
	tk->str = NULL;
	tk->str_bak = NULL;
	free (tk);
}

void	tk_lstclear(t_tk **lst)
{
	t_tk	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		tk_lstdelone(*lst);
		*lst = NULL;
		*lst = temp;
	}
}

int	calc_word_len(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != '|' && s[i] != ';' && s[i] != '>' && s[i] != '<')
	{
		if (s[i] == '\\' && s[i + 1])
			i += 2;
		else if (s[i] == '\'' || s[i] == '\"')
		{
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
		}
		else
			i++;
	}
	return (i);
}
