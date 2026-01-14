/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:31:24 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:31:45 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_shlvl(t_env **env)
{
	char	*shlvl_str;
	int		shlvl;

	if (!get_env_value(*env, "SHLVL"))
		set_env_value(env, "SHLVL", "1");
	else
	{
		shlvl_str = get_env_value(*env, "SHLVL");
		shlvl = ft_atoi(shlvl_str) + 1;
		shlvl_str = ft_itoa(shlvl);
		if (shlvl_str)
		{
			set_env_value(env, "SHLVL", shlvl_str);
			free(shlvl_str);
		}
	}
}

static void	init_minimal_env(t_env **env)
{
	char	cwd[PATH_MAX];

	if (!get_env_value(*env, "PWD"))
	{
		if (getcwd(cwd, sizeof(cwd)))
			set_env_value(env, "PWD", cwd);
	}
	init_shlvl(env);
	if (!get_env_value(*env, "PATH"))
		set_env_value(env, "PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!get_env_value(*env, "_"))
		set_env_value(env, "_", "/usr/bin/env");
}

void	init_io(t_cmd *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof(t_io_fds));
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_del = NULL;
		cmd->io_fds->heredoc_expand = 1;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_bak = -1;
		cmd->io_fds->stdout_bak = -1;
	}
}

int	init_shell(t_sh *sh, char **env)
{
	t_env	*env_list;

	ft_memset(sh, 0, sizeof(t_sh));
	env_list = init_env_list(env);
	sh->env = env_list;
	init_minimal_env(&sh->env);
	if (!sh->env)
	{
		fd_putstr(2, "Environment not initialized", 1);
		return (0);
	}
	sh->env->sh = sh;
	sh->pid = -1;
	return (1);
}
