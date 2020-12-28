/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_3d_object_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:34:25 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 17:00:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void			l3d_3d_object_triangle_copy_and_set(t_3d_object *dst,
					t_3d_object *src)
{
	int32_t		i;
	int32_t		j;

	i = -1;
	while (++i < src->num_triangles)
	{
		dst->triangles[i].parent = dst;
		l3d_triangle_set(&dst->triangles[i], (t_vertex*[3]){
			dst->vertices[src->triangles[i].vtc_indices[0]],
			dst->vertices[src->triangles[i].vtc_indices[1]],
			dst->vertices[src->triangles[i].vtc_indices[2]]}, dst);
		j = -1;
		while (++j < 3)
		{
			ml_vector2_copy(src->triangles[i].uvs[j], dst->triangles[i].uvs[j]);
			dst->triangles[i].vtc_indices[j] = src->triangles[i].vtc_indices[j];
			ml_vector2_copy(src->triangles[i].normals[j],
				dst->triangles[i].normals[j]);
		}
	}
}

/*
** Deeply copies 3d object, though the material
** texture pointer data isn't copied.
*/

t_3d_object		*l3d_3d_object_copy(t_3d_object *src)
{
	t_3d_object	*dst;
	int32_t		i;

	dst = l3d_3d_object_create(src->num_vertices, src->num_triangles);
	if (!dst || !src)
		return (NULL);
	ml_matrix4_copy(src->scale, dst->scale);
	ml_vector3_copy(src->position, dst->position);
	ml_matrix4_copy(src->rotation, dst->rotation);
	ft_memcpy(&dst->aabb, &src->aabb, sizeof(t_box3d));
	ft_memcpy(dst->material, src->material, sizeof(t_material));
	i = -1;
	while (++i < src->num_vertices)
		ft_memcpy(dst->vertices[i], src->vertices[i], sizeof(t_vertex));
	l3d_3d_object_triangle_copy_and_set(dst, src);
	return (dst);
}

/*
** Copies an object apart from any of its pointer content.
** This is used e.g. in reading obj from a file after which all triangles,
** vertices, textures etc. are filled later.
*/

t_3d_object		*l3d_3d_object_shallow_copy(t_3d_object *src)
{
	t_3d_object	*dst;

	dst = l3d_3d_object_create(src->num_vertices, src->num_triangles);
	if (!dst || !src)
		return (NULL);
	ml_matrix4_copy(src->scale, dst->scale);
	ml_vector3_copy(src->position, dst->position);
	ml_matrix4_copy(src->rotation, dst->rotation);
	ft_memcpy(&dst->aabb, &src->aabb, sizeof(t_box3d));
	ft_memset(dst->material, 0, sizeof(t_material));
	return (dst);
}

void			l3d_object_set_shading_opts(t_3d_object *obj,
					t_shading_opts opts)
{
	obj->material->shading_opts = opts;
}

void			l3d_object_set_texture(t_3d_object *obj,
					t_surface *texture)
{
	obj->material->texture = texture;
}

void			l3d_object_set_normal_map(t_3d_object *obj,
					t_surface *normal_map)
{
	obj->material->texture = normal_map;
}
