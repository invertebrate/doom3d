/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/02 23:49:15 by ahakanen         ###   ########.fr       */
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


float			pitch_from_rotation_matrix(t_mat4 rotation)
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
	t_npc	npc;

	if (obj->type == object_type_npc)
	{
		if (obj->params_type == npc_type_default)
		{
			npc_default(app, &npc);
		}
		else
			return ;
		npc.angle = pitch_from_rotation_matrix(obj->rotation) * 180 / M_PI;
		l3d_3d_object_set_params(obj, &npc, sizeof(t_npc), npc.type);
		npc_animation_3d_init(app, obj);
	}
	else if (obj->type == object_type_trigger)
	{
		if (obj->params_type == trigger_weapon_drop_shotgun)
		{

		}
	}
	else if (obj->type == object_type_path)
		path_node_init(obj);
}

static int32_t	read_objects(t_doom3d *app, char *contents)
{
	int32_t		i;
	int32_t		j;
	t_3d_object	*obj;
	int32_t		offset;

	i = -1;
	offset = 0;
	while (++i < (int32_t)app->active_scene->num_objects)
	{
		obj = l3d_3d_object_shallow_copy((t_3d_object*)(contents + offset));
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

static int32_t	read_path_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	t_path_node	*path_node;
	int32_t		num_path_nodes;
	int32_t		i;
	int32_t		j;

	offset = 0;
	num_path_nodes = 0;
	// Count path node objects
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_path)
			num_path_nodes++;
	i = -1;
	while (++i < num_path_nodes)
	{
		// Read object id
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		path_node = obj->params;
		// Read that object's number of neighbors
		ft_memcpy(&path_node->num_neighbors, contents + offset, sizeof(int32_t));
		offset += sizeof(int32_t);
		// Set neighbors
		j = -1;
		while (++j < path_node->num_neighbors)
		{
			// Read neighbor id
			ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			// Set neighbor
			obj = find_object_by_id(app, object_id);
			path_node->neighbors[j] = obj;
		}
	}
	return (offset);
}

static int32_t	read_patrol_path_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	t_npc		*npc;
	int32_t		num_npcs;
	int32_t		i;
	int32_t		j;

	offset = 0;
	num_npcs = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_npc)
			num_npcs++;
	i = -1;
	while (++i < num_npcs)
	{
		// Read object id
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		npc = obj->params;
		// Read that object's number of neighbors
		ft_memcpy(&npc->num_patrol_path_nodes, contents + offset, sizeof(int32_t));
		offset += sizeof(int32_t);
		// Set neighbors
		j = -1;
		while (++j < npc->num_patrol_path_nodes)
		{
			// Read neighbor id
			ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			obj = find_object_by_id(app, object_id);
			npc->patrol_path[j] = obj;
		}
	}
	return (offset);
}

void			read_map(t_doom3d *app, const char *map_name)
{
	t_file_contents	*file;
	char			filename[128];
	char			header[4];
	int32_t			offset;

	ft_sprintf(filename, "assets/map_data/%s", map_name);
	file = read_file(filename);
	if (!file)
		exit(EXIT_FAILURE);
	ft_memcpy(&header, file->buf, (offset = 4));
	if (!ft_strequ(header, "MAP\0"))
		error_check(true,
		"Invalid file, not a map file. First 4 bytes must be MAP\0");
	ft_memcpy(&app->active_scene->num_objects, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	offset += read_objects(app, file->buf + offset);
	offset += read_path_information(app, file->buf + offset);
	offset += read_patrol_path_information(app, file->buf + offset);
	destroy_file_contents(file);
	ft_printf("Loaded map: %s\nNum objects %u\n", map_name,
		app->active_scene->num_objects);
	//path_objects_set_neighbours(app);
}
