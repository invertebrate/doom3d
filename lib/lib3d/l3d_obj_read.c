/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_obj_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:48:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Allocates temporary content for obj data struct
*/

void					l3d_obj_content_allocate(t_obj *o)
{
	error_check(!(o->v = malloc(sizeof(t_vec3) * L3D_MAX_OBJ_VERTICES)),
		"Failed to malloc obj vs");
	error_check(!(o->vt = malloc(sizeof(t_vec2) * L3D_MAX_OBJ_VERTICES)),
		"Failed to malloc obj v textures");
	error_check(!(o->vn = malloc(sizeof(t_vec3) * L3D_MAX_OBJ_VERTICES)),
		"Failed to malloc obj v normals");
	error_check(!(o->triangles =
		malloc(sizeof(uint32_t) * 9 * L3D_MAX_OBJ_TRIANGLES)),
		"Failed to malloc obj triangles");
}

static void				set_3d_object_triangles_and_indices(
							t_obj *in, t_3d_object *out, int32_t i)
{
	out->triangles[i].vtc_indices[0] = in->triangles[i * 9 + 0 * 3 + 0] - 1;
	out->triangles[i].vtc_indices[1] = in->triangles[i * 9 + 1 * 3 + 0] - 1;
	out->triangles[i].vtc_indices[2] = in->triangles[i * 9 + 2 * 3 + 0] - 1;
	l3d_triangle_set(&out->triangles[i], (t_vertex*[3]){
		out->vertices[out->triangles[i].vtc_indices[0]],
		out->vertices[out->triangles[i].vtc_indices[1]],
		out->vertices[out->triangles[i].vtc_indices[2]]}, out);
}

/*
** Transforms a single obj data struct into t_3d_object.
** @prev_i = previous object's max indices to adjust for multi-object
** read...
*/

static void				obj_to_3d_object(t_obj *in, t_3d_object *out)
{
	int32_t		i;
	int32_t		j;
	int32_t		v_i;
	int32_t		vt_i;
	int32_t		vn_i;

	i = -1;
	while (++i < (int32_t)in->num_triangles)
	{
		j = -1;
		while (++j < 3)
		{
			v_i = in->triangles[i * 9 + j * 3 + 0] - 1;
			vt_i = in->triangles[i * 9 + j * 3 + 1] - 1;
			vn_i = in->triangles[i * 9 + j * 3 + 2] - 1;
			l3d_3d_object_set_vertex(out->vertices[v_i], in->v[v_i]);
			ml_vector2_copy(in->vt[vt_i], out->triangles[i].uvs[j]);
			ml_vector3_copy(in->vn[vn_i], out->triangles[i].normals[j]);
		}
		set_3d_object_triangles_and_indices(in, out, i);
	}
}

/*
** Loops through read objects and consolidates them as t_3d_objects to an
** array. Saves the number of objects to inputed num_objects ref.
*/

static t_3d_object		*l3d_3d_object_from_obj(t_obj *obj, t_surface *texture,
							t_surface *normal_map)
{
	t_3d_object	*l3d_object;

	l3d_object = l3d_3d_object_create(obj->num_vertices, obj->num_triangles);
	if (texture)
		l3d_object->material->texture = texture;
	if (normal_map)
		l3d_object->material->normal_map = normal_map;
	obj_to_3d_object(obj, l3d_object);
	l3d_object->num_triangles = obj->num_triangles;
	l3d_object->num_vertices = obj->num_vertices;
	free(obj->v);
	free(obj->vt);
	free(obj->vn);
	free(obj->triangles);
	l3d_object_aabb_update(l3d_object);
	return (l3d_object);
}

/*
** Reads obj file and outputs a list of t_3d_objects saving their number
** into inputted num_objects ref. Invalid obj content will exit, so NULL
** is not returned.
*/

t_3d_object				*l3d_read_obj(const char *filename, t_surface *texture,
							t_surface *normal_map)
{
	t_file_contents	*obj_file;
	t_obj			obj;

	error_check(!(obj_file = read_file(filename)), "Failed read obj file");
	l3d_obj_str_parse((char*)obj_file->buf, &obj);
	if (!l3d_is_valid_obj(&obj))
		return (NULL);
	destroy_file_contents(obj_file);
	return (l3d_3d_object_from_obj(&obj, texture, normal_map));
}
