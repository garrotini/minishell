/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:54 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:30:54 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new_node->sh = NULL;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

static t_env	*process_env_entry(char *envp_entry, t_env *head)
{
	int		key_len;
	char	*key;
	char	*value;
	t_env	*new_node;

	key_len = find_key(envp_entry);
	key = ft_substr(envp_entry, 0, key_len);
	if (!key)
		return (free_list(head), NULL);
	value = ft_substr(envp_entry, key_len + 1, ft_strlen(envp_entry)
			- key_len - 1);
	if (!value)
		return (free(key), free_list(head), NULL);
	new_node = create_env_node(key, value);
	if (!new_node)
		return (free_list(head), NULL);
	return (new_node);
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = process_env_entry(envp[i], head);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

int	find_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	free_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}
