/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_3d_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:36:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void			l3d_3d_object_debug_print(t_3d_object *obj)
{
	int32_t	i;

	ft_printf("Obj: vertices %d, triangles %d\n", obj->num_vertices,
		obj->num_triangles);
	if (obj->material)
		ft_printf("Material: width %d, height %d, pixels: %p\n",
			obj->material->texture->w, obj->material->texture->h,
				obj->material->texture->pixels);
	else
		ft_printf("Material: NULL");
	ft_printf("Pos: ");
	ml_vector3_print(obj->position);
	ft_printf("Scale:\n");
	ml_matrix4_print(obj->scale);
	ft_printf("Rotation:\n");
	ml_matrix4_print(obj->rotation);
	ft_printf("Vertices:\n");
	i = -1;
	while (++i < obj->num_vertices)
		ml_vector3_print(obj->vertices[i]->pos);
}

/*
** Creates an empty 3d object allocating space for vertices, triangles and
** text coords.
*/

t_3d_object		*l3d_3d_object_create(uint32_t num_vertices,
					uint32_t num_triangles)
{
	t_3d_object	*object;
	int32_t		i;

	error_check(!(object = malloc(sizeof(*object))),
		"Failed to malloc 3d obj");
	ft_memset(object, 0, sizeof(t_3d_object));
	error_check(!(object->vertices = malloc(sizeof(t_vertex*) * num_vertices)),
		"Failed to malloc 3d obj vertices");
	i = -1;
	while (++i < (int32_t)num_vertices)
		error_check(!(object->vertices[i] = malloc(sizeof(t_vertex))),
			"Failed to malloc vertex");
	error_check(!(object->triangles =
		malloc(sizeof(t_triangle) * num_triangles)),
		"Failed to malloc 3d obj triangles");
	error_check(!(object->material = malloc(sizeof(t_material))),
		"Failed to malloc 3d obj material");
	ml_matrix4_id(object->rotation);
	ml_matrix4_id(object->scale);
	ml_vector3_set(object->position, 0, 0, 0);
	object->num_triangles = num_triangles;
	object->num_vertices = num_vertices;
	return (object);
}

/*
** Destroys a 3d object.
*/

void			l3d_3d_object_destroy(t_3d_object *object)
{
	int		i;

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
