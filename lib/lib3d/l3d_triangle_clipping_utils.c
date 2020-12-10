/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_clipping_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:30:52 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 19:03:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
**	Interpolates uv coordinates for the new vertices of the clipped triangle
**	Uses the z coordinate (i = 2) to interpolate because that is the most likely
**	one to have proper values for linear interpolation. X causes glitches.
*/

t_bool			l3d_interpolate_clipped_uv(t_triangle *triangle,
						int32_t *limits, t_vec3 hit, t_vec2 result)
{
	int		i;
	double	fraction;

	fraction = 0.0;
	i = 2;
	if (fabs(triangle->vtc[limits[0]]->pos[i] -
		triangle->vtc[limits[1]]->pos[i]) < L3D_EPSILON)
	{
		ft_dprintf(2, "Degenerate triangles passed to clipping\n");
		return (false);
	}
	fraction = fabs(hit[i] - triangle->vtc[limits[0]]->pos[i]) /
		fabs(triangle->vtc[limits[0]]->pos[i] -
		triangle->vtc[limits[1]]->pos[i]);
	result[0] = triangle->uvs[limits[0]][0] * (1 - fraction) +
		triangle->uvs[limits[1]][0] * (fraction);
	result[1] = triangle->uvs[limits[0]][1] * (1 - fraction) +
		triangle->uvs[limits[1]][1] * (fraction);
	return (true);
}

/*
**	Checks if the triangle clips with a plane and gives the indices for the
**	vertices that are on the positive side of the plane if it is clipping.
**	Return value is the number of vertices on the positive side of the plane.
*/

static t_bool	behind(t_plane *near, t_vec3 point)
{
	t_vec3 pldir;
	t_vec3 point_from_plane;

	ml_vector3_mul(near->normal, near->d, pldir);
	ml_vector3_sub(point, pldir, point_from_plane);
	if (ml_vector3_dot(pldir, point_from_plane) < 0)
		return (true);
	return (false);
}

int32_t			l3d_triangle_clipping_case(t_triangle *triangle,
						t_plane *near, int32_t *point_indices)
{
	int32_t		i;
	t_bool		b;
	t_vertex	*vtc[3];

	i = -1;
	while (++i < 3)
	{
		vtc[0] = triangle->vtc[i];
		vtc[1] = triangle->vtc[(i + 1) % 3];
		vtc[2] = triangle->vtc[(i + 2) % 3];
		b = behind(near, vtc[0]->pos);
		if (b && !(behind(near, vtc[1]->pos)) && !(behind(near, vtc[2]->pos)))
		{
			point_indices[0] = i;
			return (2);
		}
		if (!b && behind(near, vtc[1]->pos) && behind(near, vtc[2]->pos))
		{
			point_indices[0] = (i + 1) % 3;
			point_indices[1] = (i + 2) % 3;
			return (1);
		}
	}
	return (0);
}
