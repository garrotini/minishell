/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:18 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:18 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_env_node(t_env **env, t_env *prev, t_env *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		*env = cur->next;
	free(cur->key);
	free(cur->value);
	free(cur);
}

static void	unset_var(char *var, t_env **env)
{
	t_env	*prev;
	t_env	*cur;

	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, var))
		{
			remove_env_node(env, prev, cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_var(args[i], env);
		i++;
	}
	return (0);
}
