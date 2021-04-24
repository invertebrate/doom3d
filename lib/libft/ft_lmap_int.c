/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:28:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:55:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Linearly maps number from input scale to output scale
*/

int		ft_lmap_int(int nb, int *in_minmax, int *out_minmax)
{
	return ((nb - in_minmax[0]) *
			(out_minmax[1] - out_minmax[0]) /
			(in_minmax[1] - in_minmax[0]) +
			out_minmax[0]);
}
