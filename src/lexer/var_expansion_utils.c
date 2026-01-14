/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:41:01 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:41:02 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_var_len(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i])
	{
		if (s[i] == '_' || (s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))
		{
			len++;
			i++;
		}
		else
			break ;
	}
	return (len);
}

char	*replace_var(char *s, int *i, char *value, int var_len)
{
	char	*temp;
	int		new_len;

	if (!value)
		value = "";
	new_len = *i + ft_strlen(value) + ft_strlen(s + *i + 1 + var_len) + 1;
	temp = malloc(sizeof(char) * new_len);
	if (!temp)
		return (free(s), NULL);
	ft_strlcpy(temp, s, *i + 1);
	ft_strlcat(temp, value, new_len);
	ft_strlcat(temp, s + *i + 1 + var_len, new_len);
	*i += ft_strlen(value);
	return (free(s), temp);
}

char	*expand_exit_code(char *s, int *i, int exit_code)
{
	char	*exit_str;
	char	*temp;
	int		new_len;

	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		return (free(s), NULL);
	new_len = *i + ft_strlen(exit_str) + ft_strlen(s + *i + 2) + 1;
	temp = malloc(sizeof(char) * new_len);
	if (!temp)
		return (free(exit_str), free(s), NULL);
	ft_strlcpy(temp, s, *i + 1);
	ft_strlcat(temp, exit_str, new_len);
	ft_strlcat(temp, s + *i + 2, new_len);
	*i += ft_strlen(exit_str);
	return (free(exit_str), free(s), temp);
}
