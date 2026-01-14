/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:49:43 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/02 22:49:44 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_digits(long n)
{
	int	ndigit;

	ndigit = 0;
	if (n < 0)
	{
		ndigit++;
		n *= -1;
	}
	while (n > 9)
	{
		ndigit++;
		n = n / 10;
	}
	ndigit++;
	return (ndigit);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		ndigit;
	long	nb;

	nb = n;
	ndigit = count_digits(nb);
	str = malloc(sizeof(char) * (ndigit + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		nb = nb * (-1);
		str[0] = '-';
	}
	i = ndigit - 1;
	while (nb > 9)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	str[i] = nb + '0';
	str[ndigit] = '\0';
	return (str);
}

int	ft_atoi(char *s)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		ret = ret * 10 + (*s - '0');
		s++;
	}
	return (ret * sign);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
