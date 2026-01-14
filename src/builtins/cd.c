/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:00 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:29:00 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cd_path(char **args, t_env **env)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value(*env, "HOME");
		if (!path)
			write(2, "minishell: cd: HOME not set\n", 28);
		return (path);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
			write(2, "minishell: cd: OLDPWD not set\n", 30);
		else
			printf("%s\n", path);
		return (path);
	}
	return (args[1]);
}

static int	change_directory(char *path, char *oldpwd)
{
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	return (0);
}

static int	update_pwd_vars(t_env **env, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("minishell: cd");
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	if (oldpwd)
		set_env_value(env, "OLDPWD", oldpwd);
	set_env_value(env, "PWD", newpwd);
	if (oldpwd)
		free(oldpwd);
	free(newpwd);
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	path = get_cd_path(args, env);
	if (!path)
	{
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	if (change_directory(path, oldpwd) != 0)
		return (1);
	return (update_pwd_vars(env, oldpwd));
}
