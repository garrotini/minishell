/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:49:00 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:49:03 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count_strings(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_arg_create(char const *s, char c, size_t *x)
{
	char	*slice;
	size_t	start;
	size_t	len;
	size_t	i;

	while (s[*x] && s[*x] == c)
		(*x)++;
	start = *x;
	len = 0;
	while (s[*x + len] != c && s[*x + len])
		len++;
	slice = (char *)malloc(len + 1);
	if (!slice)
		return (NULL);
	i = 0;
	while (i < len)
	{
		slice[i] = s[start + i];
		i++;
	}
	slice[len] = '\0';
	*x += len;
	return (slice);
}

void	ft_free(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	while (i > 0)
		free(argv[(i--) - 1]);
	free(argv);
}

static void	ft_slicer(char **argv, char const *str, char c, int n_args)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while ((int)y < n_args)
	{
		argv[y] = ft_arg_create(str, c, &x);
		if (!argv[y])
		{
			ft_free(argv);
			return ;
		}
		y++;
	}
	argv[y] = (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**slices;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_count_strings(s, c);
	if (!count)
		return (NULL);
	slices = (char **)malloc(sizeof(char *) * (count + 2));
	if (!slices)
		return (NULL);
	ft_slicer(slices, s, c, count);
	return (slices);
}
