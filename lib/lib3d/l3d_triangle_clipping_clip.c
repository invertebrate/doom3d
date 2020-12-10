/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_clipping_clip.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:38:17 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:48:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void			set_clip_two_triangle_ray_hits(t_triangle *triangle,
						t_plane *plane, int32_t *indices, t_vec3 hits[2])
{
	t_vec3	dirs[2];
	t_ray	rays[2];

	ml_vector3_sub(triangle->vtc[indices[0]]->pos,
		triangle->vtc[(indices[0] + 1) % 3]->pos, dirs[0]);
	ml_vector3_sub(triangle->vtc[indices[0]]->pos,
		triangle->vtc[(indices[0] + 2) % 3]->pos, dirs[1]);
	l3d_ray_set(dirs[0], triangle->vtc[indices[0]]->pos, &rays[0]);
	l3d_ray_set(dirs[1], triangle->vtc[indices[0]]->pos, &rays[1]);
	l3d_plane_ray_hit(plane, &rays[0], hits[0]);
	l3d_plane_ray_hit(plane, &rays[1], hits[1]);
}

static void			set_clip_two_triangle_vertices(t_triangle *triangle,
						int32_t *indices, t_vec3 hits[2],
						t_triangle *result_tris)
{
	ml_vector3_copy(triangle->vtc[(indices[0] + 1) % 3]->pos,
		result_tris[0].vtc[0]->pos);
	ml_vector3_copy(hits[0], result_tris[0].vtc[1]->pos);
	ml_vector3_copy(triangle->vtc[(indices[0] + 2) % 3]->pos,
		result_tris[0].vtc[2]->pos);
	ml_vector3_copy(triangle->vtc[(indices[0] + 2) % 3]->pos,
		result_tris[1].vtc[0]->pos);
	ml_vector3_copy(hits[0], result_tris[1].vtc[1]->pos);
	ml_vector3_copy(hits[1], result_tris[1].vtc[2]->pos);
}

/*
**	Clips a triangle that is intersecting a plane. The result is either one or
**	two triangles on the positive side of the plane.
*/

t_bool				create_two_clipped_triangles(t_triangle *triangle,
						t_plane *plane, int32_t *indices,
						t_triangle *result_tris)
{
	t_vec3	hits[2];
	t_vec2	uvs[2];

	set_clip_two_triangle_ray_hits(triangle, plane, indices, hits);
	set_clip_two_triangle_vertices(triangle, indices, hits, result_tris);
	if (!(l3d_interpolate_clipped_uv(triangle, (int[2]){indices[0],
		(indices[0] + 1) % 3}, hits[0], uvs[0])))
		return (false);
	if (!(l3d_interpolate_clipped_uv(triangle, (int[2]){indices[0],
		(indices[0] + 2) % 3}, hits[1], uvs[1])))
		return (false);
	ml_vector2_copy(triangle->uvs[(indices[0] + 1) % 3],
		result_tris[0].uvs[0]);
	ml_vector2_copy(uvs[0], result_tris[0].uvs[1]);
	ml_vector2_copy(triangle->uvs[(indices[0] + 2) % 3],
		result_tris[0].uvs[2]);
	ml_vector2_copy(triangle->uvs[(indices[0] + 2) % 3],
		result_tris[1].uvs[0]);
	ml_vector2_copy(uvs[0], result_tris[1].uvs[1]);
	ml_vector2_copy(uvs[1], result_tris[1].uvs[2]);
	result_tris[0].clipped = true;
	result_tris[1].clipped = true;
	return (true);
}

static void			set_clip_one_triangle_ray_hits(t_triangle *triangle,
						t_plane *plane, int32_t *indices, t_vec3 hits[2])
{
	t_vec3	dirs[2];
	t_ray	rays[2];

	ml_vector3_sub(triangle->vtc[(indices[0] + 2) % 3]->pos,
		triangle->vtc[(indices[0] + 1) % 3]->pos, dirs[0]);
	ml_vector3_sub(triangle->vtc[(indices[0] + 2) % 3]->pos,
		triangle->vtc[(indices[0]) % 3]->pos, dirs[1]);
	l3d_ray_set(dirs[0], triangle->vtc[(indices[0] + 2) % 3]->pos, &rays[0]);
	l3d_ray_set(dirs[1], triangle->vtc[(indices[0] + 2) % 3]->pos, &rays[1]);
	l3d_plane_ray_hit(plane, &rays[0], hits[0]);
	l3d_plane_ray_hit(plane, &rays[1], hits[1]);
}

t_bool				create_one_clipped_triangle(t_triangle *triangle,
						t_plane *plane, int32_t *indices,
						t_triangle *result_tris)
{
	t_vec3	hits[2];
	t_vec2	uvs[2];

	set_clip_one_triangle_ray_hits(triangle, plane, indices, hits);
	ml_vector3_copy(triangle->vtc[(indices[0] + 2) % 3]->pos,
		result_tris[0].vtc[0]->pos);
	ml_vector3_copy(hits[0], result_tris[0].vtc[1]->pos);
	ml_vector3_copy(hits[1], result_tris[0].vtc[2]->pos);
	if (!(l3d_interpolate_clipped_uv(triangle, (int[2]){(indices[0] + 1) % 3,
		(indices[0] + 2) % 3}, hits[0], uvs[0])))
		return (false);
	if (!(l3d_interpolate_clipped_uv(triangle, (int[2]){(indices[0]) % 3,
		(indices[0] + 2) % 3}, hits[1], uvs[1])))
		return (false);
	ml_vector2_copy(triangle->uvs[(indices[0] + 2) % 3], result_tris->uvs[0]);
	ml_vector2_copy(uvs[0], result_tris[0].uvs[1]);
	ml_vector2_copy(uvs[1], result_tris[0].uvs[2]);
	result_tris[0].clipped = true;
	return (true);
}
