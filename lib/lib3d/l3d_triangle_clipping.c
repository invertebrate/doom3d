/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_clipping.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/28 19:29:18 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
**	Clips a triangle that is intersecting the plane. Forms either 1 or 2 new
**	triangles depending on intersection case. Vertex attributes are interpolated
**	1. Determine the clipping case (1 or 2 triangles needed)
**	2. Calculate clipping points on plane (using plane intersection)
**	3. Interpolate vertex attributes to new points
**	4. Form triangle(s) from new points
*/

int32_t	l3d_clip_triangle(t_triangle *triangle, t_plane *plane,
									t_triangle *result_triangles[2])
{
	int		clip_case;
	int		indices[2];

	indices[0] = 4;
	indices[1] = 4;
	clip_case = l3d_triangle_clipping_case(triangle, plane, indices);
	if (clip_case == 2)
	{
		if (!(create_two_clipped_triangles(triangle, plane, indices,
					result_triangles)))
			return (0);
		return (2);
	}
	else if (clip_case == 1)
	{
		if (!(create_one_clipped_triangle(triangle, plane, indices,
					result_triangles)))
			return (0);
		return (1);
	}
	else
	{
		return (0);
	}
}

void	l3d_init_clipped_triangles(t_triangle *clipped_tris[2])
{
	int32_t		i;

	i = -1;
	while (++i < 3)
	{
		clipped_tris[0]->vtc[i]->color = 0;
		clipped_tris[1]->vtc[i]->color = 0;
		ml_vector3_set_all(clipped_tris[0]->vtc[i]->pos, 0.0);
		ml_vector3_set_all(clipped_tris[1]->vtc[i]->pos, 0.0);
	}
}
