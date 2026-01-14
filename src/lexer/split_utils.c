/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:40:26 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:40:27 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	count_av_size(char **av)
{
	size_t	i;

	i = 0;
	if (av)
		while (av[i])
			i++;
	return (i);
}

// create new string from source with given length
char	*create_tk_str(char *s, size_t len)
{
	char	*neo_s;

	neo_s = malloc(len + 1);
	if (!neo_s)
		return (NULL);
	ft_strlcpy(neo_s, s, len + 1);
	neo_s[len] = 0;
	return (neo_s);
}

// add string to array, expanding array by one element
char	**add_str(char **av, char *s, size_t len)
{
	size_t	i;
	size_t	j;
	char	**neo_av;
	char	*neo_s;

	i = count_av_size(av);
	neo_av = malloc(sizeof(char *) * (i + 2));
	if (!neo_av)
		return (NULL);
	j = 0;
	while (j < i)
	{
		neo_av[j] = av[j];
		j++;
	}
	neo_s = create_tk_str(s, len);
	if (!neo_s)
		return (free(neo_av), NULL);
	neo_av[i] = neo_s;
	neo_av[i + 1] = NULL;
	if (av)
		free(av);
	return (neo_av);
}

// Remove $"" or $'' pattern from string at position i
char	*rm_dollar_pattern(char *s, int i)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(s) - 2));
	if (!tmp)
		return (free(s), NULL);
	ft_strlcat(tmp, s, i + 1);
	ft_strlcat(tmp + i, s + i + 3, ft_strlen(s + i + 3) + 1);
	free(s);
	return (tmp);
}

// Remove $"" and $'' patterns from string
char	*rm_dollar_quote(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (ft_strchr(s + i, '$'))
	{
		i = ft_strchr(s + i, '$') - s;
		if (!ft_strncmp(s + i, "$\"\"", 3) || !ft_strncmp(s + i, "$\'\'", 3))
		{
			s = rm_dollar_pattern(s, i);
			if (!s)
				return (NULL);
		}
		else
			i++;
	}
	return (s);
}
