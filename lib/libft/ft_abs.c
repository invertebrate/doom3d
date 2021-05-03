/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:55:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:32:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_abs(double nb)
{
	if (nb >= 0)
		return (nb);
	else
		return (-nb);
}

long double	ft_abs_long_double(long double nb)
{
	if (nb >= 0)
		return (nb);
	else
		return (-nb);
}
