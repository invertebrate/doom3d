/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:05:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:27:36 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_npc_object(t_doom3d *app, t_3d_object *obj)
{
	t_npc		npc;

	ft_memset(&npc, 0, sizeof(t_npc));
	if (obj->params_type == npc_type_monster01
		|| obj->params_type == npc_type_monster01_a)
		npc_default(app, &npc, obj);
	else if (obj->params_type == npc_type_monster02
		|| obj->params_type == npc_type_monster01_range)
		npc_ranged(app, &npc, obj);
	else if (obj->params_type == npc_type_elevator)
		npc_elevator(app, &npc, obj);
	else if (obj->params_type == npc_type_crate)
		npc_crate(app, &npc, obj);
	else
		return ;
	npc_monster01(app, &npc, obj->params_type);
	npc.angle = pitch_from_rotation_matrix(obj->rotation) * 180 / M_PI;
	l3d_3d_object_set_params(obj, &npc, sizeof(t_npc), npc.type);
	if (obj->params_type != npc_type_elevator)
		npc_animation_3d_init(app, obj);
}

/*
** Based on obj type & obj params type sets the params to correct data
** E.g. obj type == npc, then check obj params type, and set npc data to
** corresponding npc type
** for npc angle:
** https://stackoverflow.com/questions/15022630/
*/

static void	set_obj_params_by_type(t_doom3d *app, t_3d_object *obj)
{
	t_trigger	trigger;

	if (!obj)
		return ;
	if (obj->type == object_type_npc)
		set_npc_object(app, obj);
	else if (obj->type == object_type_trigger)
	{
		ft_memset(&trigger, 0, sizeof(t_trigger));
		trigger.parent = obj;
		trigger.key_id = -1;
		l3d_3d_object_set_params(obj, &trigger,
			sizeof(t_trigger), obj->params_type);
	}
	else if (obj->type == object_type_path)
		path_node_init(obj);
}

static int32_t	read_object_triangles_and_vertices(char *contents,
					t_3d_object *obj, int32_t offset)
{
	int32_t		j;

	j = -1;
	while (++j < (int32_t)obj->num_vertices)
	{
		ft_memcpy(obj->vertices[j], contents + offset, sizeof(t_vertex));
		offset += sizeof(t_vertex);
	}
	j = -1;
	while (++j < (int32_t)obj->num_triangles)
	{
		ft_memcpy(&obj->triangles[j], contents + offset, sizeof(t_triangle));
		offset += sizeof(t_triangle);
	}
	return (offset);
}

/*
**	This is mainly for older maps so that their object shading modes get
**	updated.
*/

static void	set_default_shading_opts(t_3d_object *obj)
{
	if (!(obj->material->shading_opts & e_shading_zero_alpha)
		&& !(obj->material->shading_opts & e_shading_invisible)
		&& !(obj->material->shading_opts & e_shading_light))
	{
		if (!(obj->material->shading_opts & e_shading_luminous))
			obj->material->shading_opts |= e_shading_standard;
	}
}

/*
** In the same order as we wrote the object bytes, we need to read them.
** 1. Read object as is (shallow copy, so pointers will point to nothing)
** 2. Read vertices
** 3. Read triangles
** 4. Read texture & normal map filenames and their lengths
** 5. Read shading opts
** 6. Set object params at runtime by saved object type
*/

int32_t	read_objects(t_doom3d *app, char *contents)
{
	t_3d_object	*obj;
	int32_t		offset;
	int32_t		i;

	i = -1;
	offset = 0;
	obj = NULL;
	while (++i < (int32_t)app->active_scene->num_objects)
	{
		error_check(!(obj
				= l3d_3d_object_shallow_copy(
					(t_3d_object *)(contents + offset))),
			"Failed to read object from map byte offset");
		offset += sizeof(t_3d_object);
		offset = read_object_triangles_and_vertices(contents, obj, offset);
		offset += read_obj_texture(obj, app, contents + offset);
		offset += read_obj_normal_map(obj, app, contents + offset);
		ft_memcpy(&obj->material->shading_opts,
			contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		l3d_3d_object_triangle_copy_and_set(obj, obj);
		set_obj_params_by_type(app, obj);
		set_default_shading_opts(obj);
		app->active_scene->objects[i] = obj;
	}
	return (offset);
}
