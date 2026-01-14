/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:13 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:13 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	process_export_arg(char *arg, t_env **env)
{
	int		eq_pos;
	char	*key;
	char	*value;

	eq_pos = find_key(arg);
	key = ft_substr(arg, 0, eq_pos);
	value = NULL;
	if (arg[eq_pos] == '=')
		value = ft_strdup(arg + eq_pos + 1);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		free(value);
		return (1);
	}
	set_env_value(env, key, value);
	free(key);
	free(value);
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
		return (print_export(*env));
	while (args[i])
	{
		if (!args[i][0] || (args[i][0] == '\'' && !args[i][1])
			|| (args[i][0] == '\"' && !args[i][1]))
		{
			i++;
			continue ;
		}
		if (process_export_arg(args[i], env))
			status = 1;
		i++;
	}
	return (status);
}
