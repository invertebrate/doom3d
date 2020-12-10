/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:12:27 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/15 15:24:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static double			fractional_part(char *str)
{
	int		zeros;
	double	frac;
	double	divider;

	str++;
	zeros = 0;
	frac = 0.0;
	while (*str && *str == '0')
	{
		str++;
		zeros++;
	}
	if (ft_isdigit(*str))
	{
		frac = (double)ft_atoi_long(str);
		divider = pow(10.0, (double)zeros + ft_ceil(log10(frac)));
		if (divider != 0.0)
			frac = frac / divider;
	}
	return (frac);
}

/*
** Turns a double *str into a double
** Int part + factional part = resulting value.
** For zero int part, sign = -1 if first char is '-'. Else 1, because atoi
** returns sign for int part.
*/

double					ft_atod(char *str)
{
	double	val;
	int		sign;

	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (0.0);
	val = (double)ft_atoi_long(str);
	sign = *str == '-' ? -1 : 1;
	while (ft_isdigit(*str) || *str == '-' || *str == '+')
		str++;
	val *= sign;
	if (*str && *str == '.')
		val += fractional_part(str);
	return (val * sign);
}
