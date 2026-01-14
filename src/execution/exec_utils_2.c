/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:50 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:28:52 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_env_entry(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

int	count_envp(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

int	fill_envp(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = join_env_entry(env);
			if (!envp[i])
				return (free_split(envp), -1);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (0);
}
