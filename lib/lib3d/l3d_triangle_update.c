/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:52:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Updates triangle centroid, ab, ac and normals
*/

void				l3d_triangle_update(t_triangle *triangle)
{
	ml_vector3_sub(triangle->vtc[1]->pos, triangle->vtc[0]->pos, triangle->ab);
	ml_vector3_sub(triangle->vtc[2]->pos, triangle->vtc[0]->pos, triangle->ac);
	l3d_triangle_centroid_update(triangle);
	l3d_triangle_normal_update(triangle);
	l3d_triangle_tangent_update(triangle);
}

/*
** Updates triangle normals. (Usually used after vertice pos changes)
*/

void				l3d_triangle_normal_update(t_triangle *triangle)
{
	ml_vector3_cross(triangle->ab, triangle->ac, triangle->normal);
	if (ml_vector3_mag(triangle->normal) < L3D_EPSILON)
		ml_vector3_set_all(triangle->normal, 1.0);
}

static void			calculate_tangent(t_triangle *triangle, float fraction,
										float *deltas)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		triangle->tangent[i] = fraction * (deltas[3] * triangle->ab[i] -
											deltas[2] * triangle->ac[i]);
	}
	if (ml_vector3_mag(triangle->tangent) < L3D_EPSILON)
		ml_vector3_set_all(triangle->tangent, 1.0);
}

static void			set_deltas(t_triangle *triangle, float *deltas)
{
	deltas[0] = triangle->uvs[1][0] - triangle->uvs[0][0];
	deltas[1] = triangle->uvs[2][0] - triangle->uvs[0][0];
	deltas[2] = triangle->uvs[1][1] - triangle->uvs[0][1];
	deltas[3] = triangle->uvs[2][1] - triangle->uvs[0][1];
}

void				l3d_triangle_tangent_update(t_triangle *triangle)
{
	t_vec3	temptangent;
	t_vec3	tempnormal;
	float	deltas[4];
	float	fraction;
	float	div;

	ml_vector3_set_all(tempnormal, 0.0);
	set_deltas(triangle, deltas);
	if ((div = (deltas[0] * deltas[3] - deltas[1] * deltas[2])) > L3D_EPSILON)
		fraction = 1.0 / div;
	else
		fraction = 1.0;
	calculate_tangent(triangle, fraction, deltas);
	ml_vector3_normalize(triangle->tangent, triangle->tangent);
	ml_vector3_normalize(triangle->normal, triangle->normalized_normal);
	ml_vector3_normalize(triangle->normal, tempnormal);
	ml_vector3_mul(tempnormal, ml_vector3_dot(triangle->tangent, tempnormal),
		temptangent);
	ml_vector3_sub(triangle->tangent, temptangent, triangle->tangent);
	ml_vector3_normalize(triangle->tangent, triangle->tangent);
	ml_vector3_cross(triangle->tangent, tempnormal, triangle->bitangent);
	if (triangle->clipped == true)
		ml_vector3_mul(triangle->bitangent, -1.0, triangle->bitangent);
}
