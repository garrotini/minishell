/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:38:57 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/08 00:39:11 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_child(t_sh *sh, int exit_code)
{
	if (!sh)
		exit(exit_code);
	close_fds(sh->cmd);
	free_sh(sh);
	free_env_list(sh->env);
	exit(exit_code);
}
