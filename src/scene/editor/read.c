/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/05 18:53:59 by ohakola          ###   ########.fr       */
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
		ft_printf("Object id %u\n", obj->id);
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
		app->active_scene->objects[i] = obj;
	}
	return (offset);
}

static int32_t	read_npcs(t_doom3d *app, char *contents)
{
	int32_t		i;
	uint32_t	object_id;
	int32_t		offset;
	t_npc		npc;

	i = -1;
	offset = 0;
	while (++i < (int32_t)app->active_scene->num_npcs)
	{
		npc_init(app, &npc);
		ft_memcpy(&npc.type, contents + offset, sizeof(t_npc_type));
		offset += sizeof(t_npc_type);
		parse_npc_type(app, &npc, npc.type);
		ft_memcpy(&npc.id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		npc.obj = find_object_by_id(app, object_id);
		ft_memcpy(npc.pos, contents + offset, sizeof(t_vec3));
		offset += sizeof(t_vec3);
		ft_memcpy(&npc.angle, contents + offset, sizeof(float));
		offset += sizeof(float);
		npc_add_to_scene(app, &npc);
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
	ft_memcpy(&app->active_scene->num_npcs, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	offset += read_objects(app, file->buf + offset);
	offset += read_npcs(app, file->buf + offset);
	destroy_file_contents(file);
	ft_printf("Loaded map: %s\nNum objects %u\nNum npcs: %u\n", map_name,
		app->active_scene->num_objects, app->active_scene->num_npcs);
}
