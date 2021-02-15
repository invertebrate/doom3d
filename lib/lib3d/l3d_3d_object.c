/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_3d_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/15 22:01:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Creates an empty 3d object allocating space for vertices, triangles and
** text coords.
*/

t_3d_object		*l3d_3d_object_create(uint32_t num_verts,
					uint32_t num_triangles)
{
	t_3d_object	*object;
	int32_t		i;

	error_check(!(object = ft_calloc(sizeof(*object))),
		"Failed to malloc 3d obj");
	object->id = l3d_random_uuid();
	error_check(!(object->vertices = ft_calloc(sizeof(t_vertex*) * num_verts)),
		"Failed to malloc 3d obj vertices");
	i = -1;
	while (++i < (int32_t)num_verts)
		error_check(!(object->vertices[i] = ft_calloc(sizeof(t_vertex))),
			"Failed to malloc vertex");
	error_check(!(object->triangles =
		ft_calloc(sizeof(t_triangle) * num_triangles)), "!3d obj triangles");
	error_check(!(object->material = ft_calloc(sizeof(t_material))),
		"Failed to malloc 3d obj material");
	ml_matrix4_id(object->rotation);
	ml_matrix4_id(object->scale);
	ml_vector3_set(object->position, 0, 0, 0);
	object->num_triangles = num_triangles;
	object->num_vertices = num_verts;
	i = -1;
	while (++i < (int32_t)num_triangles)
		object->triangles[i].parent = object;
	return (object);
}

/*
** Destroys a 3d object.
*/

void			l3d_3d_object_destroy(t_3d_object *object)
{
	int		i;

	free(object->params);
	free(object->triangles);
	i = -1;
	while (++i < object->num_vertices)
		free(object->vertices[i]);
	free(object->material);
	free(object->vertices);
	free(object);
	object = NULL;
}

/*
** Just a space saving function to set obj data on 3d object
** (normals, texture coords and position)
*/

void			l3d_3d_object_set_vertex(t_vertex *vertex, t_vec3 pos)
{
	ml_vector3_copy(pos, vertex->pos);
	vertex->color = 0xFFFFFFFF;
}

void			l3d_3d_object_set_params(t_3d_object *object,
					void *params, uint32_t params_size, uint32_t params_type)
{
	if (params_size > 0)
	{
		error_check(!(object->params = ft_calloc(params_size)),
			"Failed to malloc obj params");
		ft_memcpy(object->params, params, params_size);
	}
	else
		object->params = NULL;
	object->params_size = params_size;
	object->params_type = params_type;
}

void			l3d_3d_object_add_light_source(t_3d_object *object,
					t_vec3 light_pos)
{
	if (object->material->num_lights < L3D_MAX_LIGHTS)
		ml_vector3_copy(light_pos,
			object->material->light_sources[object->material->num_lights++]);
	else
		ft_printf("Too many lights set for object %d, max: %d\n",
			object->id, L3D_MAX_LIGHTS);
}
