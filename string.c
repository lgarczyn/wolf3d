/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:31:41 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/02/02 10:32:13 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
		if (*s1 != *s2)
			return (*s1 - *s2);
		else
		{
			s1++;
			s2++;
		}
	return (0);
}

void			ft_putstr(char *str)
{
	int			len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

int				ft_intlen(int32_t n)
{
	int			sign;

	sign = n < 0;
	if (sign)
		n = -n;
	if (n < 10)
		return (1 + sign);
	if (n < 100)
		return (2 + sign);
	if (n < 1000)
		return (3 + sign);
	if (n < 10000)
		return (4 + sign);
	if (n < 100000)
		return (5 + sign);
	if (n < 1000000)
		return (6 + sign);
	if (n < 10000000)
		return (7 + sign);
	if (n < 100000000)
		return (8 + sign);
	if (n < 1000000000)
		return (9 + sign);
	return (10 + sign);
}

char			*ft_itoa(size_t n, char *str)
{
	int			i;

	i = (int)ft_intlen(n);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int				ft_atoi(char *str)
{
	int			i;
	int			n;

	n = 0;
	i = -1;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9')
			n = n * 10 + str[i] - '0';
		else
			return (-1);
	if (i == 0)
		return (-1);
	return (n);
}
