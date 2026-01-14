/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:50 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:28:52 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	update_existing_env(t_env *env, const char *key, char *dup_value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = dup_value;
			return (0);
		}
		env = env->next;
	}
	return (1);
}

static t_env	*create_new_env_node(const char *key, char *dup_value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(dup_value);
		return (NULL);
	}
	new_node->sh = NULL;
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(dup_value);
		free(new_node);
		return (NULL);
	}
	new_node->value = dup_value;
	new_node->next = NULL;
	return (new_node);
}

int	set_env_value(t_env **env, const char *key, const char *value)
{
	char	*dup_value;
	t_env	*new_node;

	if (value)
		dup_value = ft_strdup(value);
	else
		dup_value = NULL;
	if (value && !dup_value)
		return (-1);
	if (update_existing_env(*env, key, dup_value) == 0)
		return (0);
	new_node = create_new_env_node(key, dup_value);
	if (!new_node)
		return (-1);
	new_node->next = *env;
	*env = new_node;
	return (0);
}
