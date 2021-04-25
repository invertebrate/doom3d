/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:05:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:07:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static int32_t	read_obj_texture(t_3d_object *obj,
					t_doom3d *app, char *contents)
{
	int32_t		len;
	int32_t		offset;
	char		buf[128];
	const char	*filename;

	ft_memcpy(&len, contents, sizeof(uint32_t));
	offset = sizeof(uint32_t);
	ft_memset(buf, 0, sizeof(buf));
	ft_memcpy(buf, contents + offset, len);
	offset += len;
	filename = texture_file_key(buf, app);
	obj->material->texture = hash_map_get(app->active_scene->textures,
		(int64_t)filename);
	if (filename)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filename);
	return (offset);
}

static int32_t	read_obj_normal_map(t_3d_object *obj,
					t_doom3d *app, char *contents)
{
	int32_t		len;
	int32_t		offset;
	char		buf[128];
	const char	*filename;

	ft_memcpy(&len, contents, sizeof(uint32_t));
	offset = sizeof(uint32_t);
	ft_memset(buf, 0, sizeof(buf));
	ft_memcpy(buf, contents + offset, len);
	offset += len;
	filename = normal_map_file_key(buf, app);
	obj->material->normal_map = hash_map_get(app->active_scene->normal_maps,
		(int64_t)filename);
	if (filename)
		hash_map_add(app->active_scene->object_normal_maps, obj->id,
			(void*)filename);
	return (offset);
}

static float	pitch_from_rotation_matrix(t_mat4 rotation)
{
	float	pitch1;
	float	pitch2;

	if (rotation[0][2] != 1 && rotation[0][2] != -1)
	{
		pitch1 = -1 * asin(rotation[0][2]);
		pitch2 = M_PI - pitch1;
		if (rotation[0][0] < 0 || rotation[2][2] < 0)
			return (pitch2);
		else
			return (pitch1);
	}
	return (rotation[0][2] > 0 ? -M_PI / 2.0 : M_PI / 2.0);
}

/*
** Based on obj type & obj params type sets the params to correct data
** E.g. obj type == npc, then check obj params type, and set npc data to
** corresponding npc type
** for npc angle:
** https://stackoverflow.com/questions/15022630/
*/

static void		set_obj_params_by_type(t_doom3d *app, t_3d_object *obj)
{
	t_npc		npc;
	t_trigger	trigger;

	if (!obj)
		return ;
	if (obj->type == object_type_npc)
	{
		ft_memset(&npc, 0, sizeof(t_npc));
		if (obj->params_type == npc_type_monster01 || obj->params_type == npc_type_monster01_a)
		{
			npc_default(app, &npc, obj);
		}
		else if (obj->params_type == npc_type_monster02 || obj->params_type == npc_type_monster01_range)
		{
			npc_ranged(app, &npc, obj);
		}
		else if (obj->params_type == npc_type_elevator)
		{
			npc_elevator(app, &npc, obj);
		}
		else if (obj->params_type == npc_type_crate)
		{
			npc_crate(app, &npc, obj);
		}
		else
			return ;
		npc_monster01(app, &npc, obj->params_type);
		npc.angle = pitch_from_rotation_matrix(obj->rotation) * 180 / M_PI;
		l3d_3d_object_set_params(obj, &npc, sizeof(t_npc), npc.type);
		//if (obj->params_type == npc_type_monster01 || obj->params_type == npc_type_monster02)
		if (obj->params_type != npc_type_elevator)
			npc_animation_3d_init(app, obj);
	}
	else if (obj->type == object_type_trigger)
	{
		ft_memset(&trigger, 0, sizeof(t_trigger));
		trigger.parent = obj;
		trigger.key_id = -1;
		l3d_3d_object_set_params(obj, &trigger, sizeof(t_trigger), obj->params_type);
	}
	else if (obj->type == object_type_path)
		path_node_init(obj);
}

int32_t			read_objects(t_doom3d *app, char *contents)
{
	int32_t		i;
	int32_t		j;
	t_3d_object	*obj;
	int32_t		offset;

	i = -1;
	offset = 0;
	obj = NULL;
	while (++i < (int32_t)app->active_scene->num_objects)
	{
		error_check(!(obj = l3d_3d_object_shallow_copy((t_3d_object*)(contents + offset))),
			"Failed to read object from map byte offset");
		offset += sizeof(t_3d_object);
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
		offset += read_obj_texture(obj, app, contents + offset);
		offset += read_obj_normal_map(obj, app, contents + offset);
		ft_memcpy(&obj->material->shading_opts,
			contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		l3d_3d_object_triangle_copy_and_set(obj, obj);
		set_obj_params_by_type(app, obj);
		app->active_scene->objects[i] = obj;
	}
	return (offset);
}
