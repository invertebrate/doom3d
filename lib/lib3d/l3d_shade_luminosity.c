/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shade_luminosity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 17:14:43 by veilo             #+#    #+#             */
/*   Updated: 2021/05/01 22:34:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	calculate_luminosity(uint32_t *pixel, uint32_t *light,
			uint32_t darkness)
{
	int			i;
	float		luminosity;

	i = -1;
	while (++i < 3)
	{
		luminosity = (float)((255 - darkness + (float)light[i]) / 255);
		if (luminosity > 1.0)
			luminosity = 1.0;
		pixel[i] = pixel[i] * luminosity;
	}
}
