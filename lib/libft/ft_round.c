/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 23:26:36 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/19 13:36:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_ceil(double num)
{
	long long int		int_part;
	t_float_dissector	fd;

	if (num == 0)
		return (num);
	fd.f = num;
	int_part = (long long int)num;
	return (fd.b.sign ? int_part : int_part + 1);
}

double		ft_floor(double num)
{
	t_float_dissector	fd;

	fd.f = num;
	return (!fd.b.sign ? (long long int)num : (long long int)num - 1);
}
