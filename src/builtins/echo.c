/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:04 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:04 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_print(char *arg, t_tk_mode mode)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && mode == IN_SQ)
		{
			i++;
			continue ;
		}
		else if (arg[i] == '\"' && mode == IN_DQ)
		{
			i++;
			continue ;
		}
		write(1, arg + i, 1);
		i++;
	}
}

static void	print_arg(char *arg, t_tk_mode mode, t_env **env)
{
	char	*home;

	if (mode == UNQUOTED)
	{
		if (ft_strcmp(arg, "~") == 0)
		{
			home = get_env_value(*env, "HOME");
			if (home)
				write(1, home, ft_strlen(home));
			else
				write(1, "~", 1);
		}
		else
			write(1, arg, ft_strlen(arg));
	}
	else if (mode == IN_SQ)
		echo_print(arg, IN_SQ);
	else if (mode == IN_DQ)
		echo_print(arg, IN_DQ);
}

int	ft_echo(char **arg, t_tk_mode *arg_mode, t_env **env)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (arg[i] && is_n_flag(arg[i]))
	{
		n_flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (arg_mode)
			print_arg(arg[i], arg_mode[i], env);
		else
			print_arg(arg[i], UNQUOTED, env);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
