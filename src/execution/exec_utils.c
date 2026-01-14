/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:29:26 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/07 13:22:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_list_to_envp(t_env *env)
{
	char	**envp;
	int		size;

	size = count_envp(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	if (fill_envp(envp, env) == -1)
		return (NULL);
	return (envp);
}

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env || !*path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full = try_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
	}
	return (free_split(paths), NULL);
}

void	exec_command(t_sh *sh, t_cmd *cmd)
{
	char	**envp;
	char	*cmd_path;

	if (!cmd || !cmd->av || !cmd->av[0])
		exit_child(sh, 127);
	cmd_path = resolve_cmd_path(cmd->av[0], sh->env);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->av[0]);
		exit_child(sh, 127);
	}
	envp = env_list_to_envp(sh->env);
	execve(cmd_path, cmd->av, envp);
	fprintf(stderr, "minishell: %s: execve failed\n", cmd->av[0]);
	free(cmd_path);
	free_split(envp);
	exit_child(sh, 126);
}
