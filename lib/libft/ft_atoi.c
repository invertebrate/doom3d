/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:02:04 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:36:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_atoi() function converts the initial portion
** of the string pointed to by str to int representation.
*/

static int	is_clearable(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	is_skippable(char c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *str)
{
	return ((int)ft_atoi_long(str));
}

static int	handle_edges(unsigned long long sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

long long int	ft_atoi_long(const char *str)
{
	unsigned long long int	res;
	unsigned long long int	sign;
	int						i;

	sign = 1;
	res = 0;
	while (*str && is_clearable(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (is_skippable(*str))
		str++;
	i = 0;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
		i++;
	}
	if (i > 19 || res >= 9223372036854775808ULL)
		return (handle_edges(sign));
	return (res * sign);
}
