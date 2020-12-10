/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:25:06 by ohakola           #+#    #+#             */
/*   Updated: 2020/03/15 17:21:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_powl(long double nb, int pow)
{
	int			i;
	long double	res;

	i = 0;
	res = 1;
	while (i < ft_abs(pow))
	{
		if (pow < 0)
			res = res * 1 / 10;
		else
			res = res * nb;
		i++;
	}
	return (res);
}

int				ft_exp_base(long double nb, int base)
{
	int				i;
	long long int	nb_int;

	i = 0;
	nb = ft_abs_long_double(nb);
	if (nb > 1)
	{
		nb_int = (long long int)nb;
		while (nb_int >= base)
		{
			nb_int = nb_int / base;
			i++;
		}
		return (i);
	}
	while (nb < 1 && nb > 0)
	{
		nb = nb * (long double)base;
		i++;
	}
	return (-i);
}
