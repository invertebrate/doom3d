/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:35:04 by veilo             #+#    #+#             */
/*   Updated: 2021/05/01 22:35:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	get_world_pos_persp_corr(t_triangle *triangle, t_vec3 baryc,
			t_vec3 world_pos)
{
	int32_t	i;
	float	az;
	float	bz;
	float	cz;
	float	inv_denom;

	az = 1.0 / triangle->vtc[0]->pos[2];
	bz = 1.0 / triangle->vtc[1]->pos[2];
	cz = 1.0 / triangle->vtc[2]->pos[2];
	inv_denom = 1.0 / (baryc[0] * az + baryc[1] * bz + baryc[2] * cz);
	i = -1;
	while (++i < 3)
		world_pos[i] = ((baryc[0] * triangle->vtc[0]->pos[i]) * az
				+ (baryc[1] * triangle->vtc[1]->pos[i]) * bz
				+ (baryc[2] * triangle->vtc[2]->pos[i]) * cz) * inv_denom;
}
