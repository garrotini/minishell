/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:38:18 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:38:18 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_env **env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args, NULL, env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args, *env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, env));
	return (1);
}
