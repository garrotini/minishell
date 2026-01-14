/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ins_tk_after(t_tk *cur, t_tk *new_tk)
{
	new_tk->next = cur->next;
	new_tk->prev = cur;
	if (cur->next)
		cur->next->prev = new_tk;
	cur->next = new_tk;
}

void	rm_tk_from_list(t_tk **head, t_tk *tk)
{
	if (tk->prev)
		tk->prev->next = tk->next;
	else
		*head = tk->next;
	if (tk->next)
		tk->next->prev = tk->prev;
}

char	**malloc_av(int n)
{
	char	**av;

	av = malloc(sizeof(char *) * (n + 1));
	if (!av)
		return (NULL);
	return (av);
}

void	fill_av(char **av, char *s, int n)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < n)
	{
		av[i] = extract_word(s, &pos);
		i++;
	}
	av[i] = NULL;
}

int	count_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
