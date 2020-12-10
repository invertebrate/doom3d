/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_clipping.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:49:08 by ohakola          ###   ########.fr       */
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

int32_t			l3d_clip_triangle(t_triangle *triangle, t_plane *plane,
									t_triangle *result_triangles)
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

void			l3d_set_clipped_triangles(t_vertex *vtc, t_triangle *source,
											t_triangle *dest_tris)
{
	int32_t		i;

	i = -1;
	ft_memcpy(&dest_tris[0], source, sizeof(t_triangle));
	ft_memcpy(&dest_tris[1], source, sizeof(t_triangle));
	while (++i < 3)
	{
		vtc[i].color = 0;
		vtc[3 + i].color = 0;
		ml_vector3_set_all(vtc[i].pos, 0.0);
		ml_vector3_set_all(vtc[3 + i].pos, 0.0);
		dest_tris[0].vtc[i] = &vtc[i];
		dest_tris[1].vtc[i] = &vtc[3 + i];
	}
}
