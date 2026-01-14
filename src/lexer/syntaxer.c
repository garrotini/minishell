/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:34 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:34 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check common syntax errors
static int	syntax_error(t_tk *temp, t_tk *prev)
{
	if ((temp->type == PIPE && prev->type == PIPE)
		|| (temp->type == PIPE && prev->type == SEMICOLON)
		|| (temp->type == SEMICOLON && prev->type == PIPE)
		|| (temp->type == SEMICOLON && prev->type == SEMICOLON)
		|| (temp->type > SEMICOLON && prev->type > SEMICOLON)
		|| (temp->type == END && prev->type == PIPE)
		|| (temp->type > SEMICOLON && prev->type >= PIPE
			&& prev->type <= SEMICOLON))
		return (1);
	return (0);
}

// checks if token WORD after PIPE is invalid
static int	check_reserved_after_pipe(t_tk *prev, t_tk *temp)
{
	if (prev->type == PIPE && temp->type == WORD && temp->str
		&& (!ft_strncmp(temp->str, ";", 2) || !ft_strncmp(temp->str, "&", 2)))
		return (perror_syntax_str(temp->str), EXIT_FAILURE);
	return (0);
}

// handle syntax error messages
static int	handle_syntax_error(t_tk *temp, t_tk *prev)
{
	if (temp->type == END && prev->type > PIPE)
		perror_syntax(0);
	else if (temp->type == END && prev)
		perror_syntax(prev->type);
	else
		perror_syntax(temp->type);
	return (1);
}

int	syntaxer(t_tk **tk)
{
	t_tk	*temp;
	t_tk	*prev;

	temp = *tk;
	prev = NULL;
	while (temp)
	{
		if (prev)
		{
			if (syntax_error(temp, prev))
				return (handle_syntax_error(temp, prev));
			if (check_reserved_after_pipe(prev, temp))
				return (EXIT_FAILURE);
		}
		if ((temp->type == PIPE || temp->type == SEMICOLON) && !prev)
			return (perror_syntax(temp->type), EXIT_FAILURE);
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
