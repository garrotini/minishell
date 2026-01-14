/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:33:40 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_count_words(t_tk *tk)
{
	int		count;
	t_tk	*temp;

	count = 0;
	temp = tk;
	while (temp && temp->type == WORD)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static void	cmd_copy_old_args(t_cmd *last_cmd, char **av, t_tk_mode *av_mode)
{
	int	i;

	i = 0;
	while (last_cmd->av[i])
	{
		av[i] = last_cmd->av[i];
		av_mode[i] = last_cmd->av_mode[i];
		i++;
	}
}

static void	cmd_join_new_args(int start, char **av,
	t_tk_mode *av_mode, t_tk **tk)
{
	int		i;
	t_tk	*temp;

	i = start;
	temp = *tk;
	while (temp && temp->type == WORD)
	{
		av[i] = ft_strdup(temp->str);
		av_mode[i] = temp->mode;
		temp = temp->next;
		i++;
	}
	av[i] = NULL;
	av_mode[i] = UNQUOTED;
	*tk = temp;
}

static void	cmd_build_arrays(t_tk **tk, t_cmd *last_cmd,
	char **av, t_tk_mode *av_mode)
{
	int	ac;

	ac = 0;
	while (last_cmd->av[ac])
		ac++;
	cmd_copy_old_args(last_cmd, av, av_mode);
	cmd_join_new_args(ac, av, av_mode, tk);
}

void	cmd_fill_av(t_tk **tk, t_cmd *last_cmd)
{
	int			new_count;
	int			old_count;
	char		**av;
	t_tk_mode	*av_mode;

	if (!*tk || (*tk)->type != WORD)
		return ;
	new_count = cmd_count_words(*tk);
	old_count = 0;
	while (last_cmd->av[old_count])
		old_count++;
	av = malloc(sizeof(char *) * (new_count + old_count + 1));
	av_mode = malloc(sizeof(t_tk_mode) * (new_count + old_count + 1));
	if (!av || !av_mode)
		return ;
	cmd_build_arrays(tk, last_cmd, av, av_mode);
	free(last_cmd->av);
	free(last_cmd->av_mode);
	last_cmd->av = av;
	last_cmd->av_mode = av_mode;
}
