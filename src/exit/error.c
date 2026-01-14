/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopes-c <jlopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:16 by jlopes-c          #+#    #+#             */
/*   Updated: 2026/01/05 15:30:17 by jlopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_msg(char *s1, char *s2, char *s3)
{
	fd_putstr(2, PS1, 0);
	fd_putstr(2, s1, 0);
	if (s2)
	{
		fd_putstr(2, ": ", 0);
		fd_putstr(2, s2, 0);
		if (s3)
		{
			fd_putstr(2, ": ", 0);
			fd_putstr(2, s3, 0);
		}
	}
	fd_putstr(2, "", 1);
}

int	perror_syntax(int type)
{
	char	*s;

	s = NULL;
	if (type == PIPE)
		s = "|";
	else if (type == SEMICOLON)
		s = ";";
	else if (type == INPUT)
		s = "<";
	else if (type == OUTPUT)
		s = ">";
	else if (type == HEREDOC)
		s = "<<";
	else if (type == APPEND)
		s = ">>";
	else if (type == 0)
		s = "newline";
	fd_putstr(2, "-minishell: syntax error near unexpected token: `", 0);
	fd_putstr(2, s, 0);
	fd_putstr(2, "'", 1);
	return (1);
}

int	perror_syntax_str(char *token)
{
	fd_putstr(2, "minishell: syntax error near unexpected token `", 0);
	fd_putstr(2, token, 0);
	fd_putstr(2, "'", 1);
	return (1);
}

int	cmd_not_found(char *cmd)
{
	fd_putstr(2, "minishell: ", 0);
	fd_putstr(2, cmd, 0);
	fd_putstr(2, ": command not found", 1);
	return (CMD_NOT_FOUND);
}

int	perror_unclosed_quote(char quote)
{
	fd_putstr(2, "minishell: syntax error: unclosed quote `", 0);
	write(2, &quote, 1);
	fd_putstr(2, "'", 1);
	return (1);
}
