/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_3d_object_transform2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:21:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:39:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		scale_uvs(t_3d_object *object, float scale_amount)
{
	int32_t	i;
	int32_t	j;

	i = -1;
	while (++i < object->num_triangles)
	{
		j = -1;
		while (++j < 3)
		{
			object->triangles[i].uvs[j][0] *= scale_amount;
			object->triangles[i].uvs[j][1] *= scale_amount;
		}
	}
}

/*
** Move object to 0, 0, 0, scale both vertices and uvs, move back (local scale)
*/

void			l3d_3d_object_scale_with_uvs(t_3d_object *object,
					float scale_amount)
{
	t_mat4	scale;
	t_mat4	new_scale;
	t_vec3	old_pos;

	ml_vector3_copy(object->position, old_pos);
	l3d_3d_object_translate(object,
		-object->position[0], -object->position[1], -object->position[2]);
	ml_matrix4_id(scale);
	scale[0][0] = scale_amount;
	scale[1][1] = scale_amount;
	scale[2][2] = scale_amount;
	l3d_3d_object_transform(object, scale);
	scale_uvs(object, scale_amount);
	ml_matrix4_mul(object->scale, scale, new_scale);
	ft_memcpy(object->scale, new_scale, sizeof(t_mat4));
	l3d_3d_object_translate(object,
		old_pos[0], old_pos[1], old_pos[2]);
	ml_vector3_copy(old_pos, object->position);
}
