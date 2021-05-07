/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:22:30 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/07 14:37:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** 1. Move vertext to 0, 0, 0
** 2. Reset rotation
** 3. Rotate by base object
** 4. Translate by base object's position
*/

static void	transform_current_object_vertex(t_animation_3d *anim,
				t_vertex *vertex,
				t_mat4 inv_rot, t_vec3 prev_translation)
{
	ml_vector3_sub(vertex->pos, prev_translation, vertex->pos);
	ml_matrix4_mul_vec3(inv_rot, vertex->pos,vertex->pos);
	ml_matrix4_mul_vec3(anim->base_object->rotation, vertex->pos, vertex->pos);
	ml_vector3_add(vertex->pos, anim->base_object->position, vertex->pos);
}

/*
** Ensure current object's position & rotation equal the base object's
** and save the previous translation to frame object
*/

static void	copy_transform_info(t_animation_3d *anim)
{
	ml_vector3_copy(anim->base_object->position,
		anim->frame_object_prev_translation[
		anim->frames_start_idx + anim->current_frame]);
	ml_vector3_copy(anim->base_object->position,
		anim->current_object->position);
	ml_matrix4_copy(anim->base_object->rotation,
		anim->current_object->rotation);
}

/*
** To save CPU time, update positions & rotations in one loop
*/

void	npc_anim_3d_transform_update(t_animation_3d *anim)
{
	int			i;
	int			j;
	t_vec3		prev_translation;
	t_3d_object	*obj;
	t_mat4		inv_rot;

	if (anim == NULL || anim->current_object == NULL
		|| anim->base_object == NULL)
		return ;
	ml_matrix4_inverse(anim->current_object->rotation, inv_rot);
	ml_vector3_copy(anim->frame_object_prev_translation[anim->frames_start_idx
		+ anim->current_frame], prev_translation);
	obj = anim->current_object;
	i = -1;
	while (++i < obj->num_vertices)
		transform_current_object_vertex(anim,
			obj->vertices[i], inv_rot, prev_translation);
	j = -1;
	while (++j < obj->num_triangles)
		l3d_triangle_update(&obj->triangles[j]);
	l3d_object_aabb_update(obj);
	copy_transform_info(anim);
}
