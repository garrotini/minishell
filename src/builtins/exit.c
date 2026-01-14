/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:10 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:10 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	validate_exit_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (args[1] && !ft_isnumber(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (0);
}

static int	get_exit_status(char **args, t_env **env)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	else if (env && *env && (*env)->sh)
		status = (*env)->sh->exit_code;
	return (status);
}

int	ft_exit(char **args, t_env **env)
{
	int		validation;
	int		status;
	t_sh	*sh;

	printf("exit\n");
	sh = NULL;
	if (env && *env && (*env)->sh)
		sh = (*env)->sh;
	validation = validate_exit_args(args);
	if (validation != 0)
	{
		if (validation == 2)
		{
			full_clean(sh);
			exit(2);
		}
		return (validation);
	}
	status = get_exit_status(args, env);
	full_clean(sh);
	exit((int)status);
}
