/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_3d_object_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Multiplies each 3d object vertex with t_mat4 transformation matrix,
** eg. translation matrix or rotation. And then updates triangle normals &
** centroids / centers.
*/

void			l3d_3d_object_transform(t_3d_object *obj, t_mat4 transform)
{
	int		i;
	int		j;

	i = -1;
	while (++i < obj->num_vertices)
		ml_matrix4_mul_vec3(transform,
			obj->vertices[i]->pos, obj->vertices[i]->pos);
	j = -1;
	while (++j < obj->num_triangles)
		l3d_triangle_update(&obj->triangles[j]);
	l3d_object_aabb_update(obj);
}

void			l3d_3d_object_translate(t_3d_object *object,
					float x, float y, float z)
{
	t_mat4	translation;

	ml_matrix4_translation(x, y, z, translation);
	l3d_3d_object_transform(object, translation);
	ml_vector3_add(object->position, (t_vec3){x, y, z}, object->position);
}

/*
** Move object to 0, 0, 0, rotate, move back
*/

void			l3d_3d_object_rotate(t_3d_object *object,
					float x, float y, float z)
{
	t_mat4	rotation;
	t_vec3	old_pos;
	t_mat4	new_rotation;

	ml_vector3_copy(object->position, old_pos);
	l3d_3d_object_translate(object,
		-object->position[0], -object->position[1], -object->position[2]);
	ml_matrix4_rotation(ml_rad(x), ml_rad(y), ml_rad(z), rotation);
	l3d_3d_object_transform(object, rotation);
	ml_matrix4_mul(object->rotation, rotation, new_rotation);
	ft_memcpy(object->rotation, new_rotation, sizeof(t_mat4));
	l3d_3d_object_translate(object,
		old_pos[0], old_pos[1], old_pos[2]);
	ml_vector3_copy(old_pos, object->position);
}

/*
** Move object to 0, 0, 0, scale, move back
*/

void			l3d_3d_object_scale(t_3d_object *object,
					float x, float y, float z)
{
	t_mat4	scale;
	t_mat4	new_scale;
	t_vec3	old_pos;

	ml_vector3_copy(object->position, old_pos);
	l3d_3d_object_translate(object,
		-object->position[0], -object->position[1], -object->position[2]);
	ml_matrix4_id(scale);
	scale[0][0] = x;
	scale[1][1] = y;
	scale[2][2] = z;
	l3d_3d_object_transform(object, scale);
	ml_matrix4_mul(object->scale, scale, new_scale);
	ft_memcpy(object->scale, new_scale, sizeof(t_mat4));
	l3d_3d_object_translate(object,
		old_pos[0], old_pos[1], old_pos[2]);
	ml_vector3_copy(old_pos, object->position);
}

/*
** Move object to 0, 0, 0, rotate, move back
*/

void			l3d_3d_object_rotate_matrix(t_3d_object *object,
					t_mat4 rotation)
{
	t_vec3	old_pos;
	t_mat4	new_rotation;

	ml_vector3_copy(object->position, old_pos);
	l3d_3d_object_translate(object,
		-object->position[0], -object->position[1], -object->position[2]);
	l3d_3d_object_transform(object, rotation);
	ml_matrix4_mul(object->rotation, rotation, new_rotation);
	ft_memcpy(object->rotation, new_rotation, sizeof(t_mat4));
	l3d_3d_object_translate(object,
		old_pos[0], old_pos[1], old_pos[2]);
	ml_vector3_copy(old_pos, object->position);
}
