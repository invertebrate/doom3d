/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 23:10:42 by ohakola          ###   ########.fr       */
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
		(int32_t)filename);
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
		(int32_t)filename);
	return (offset);
}

static void	read_objects(t_doom3d *app, char *contents)
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
		app->active_scene->objects[i] = obj;
	}
}

void		read_map(t_doom3d *app, const char *filename)
{
	t_file_contents	*file;
	char			header[4];
	uint32_t		num_objects;
	int32_t			offset;

	file = read_file(filename);
	ft_memcpy(&header, file->buf, (offset = 4));
	if (!ft_strequ(header, "MAP\0"))
		error_check(true,
		"Invalid file, not a map file. First 4 bytes must be MAP\0");
	ft_memcpy(&num_objects, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	app->active_scene->num_objects = num_objects;
	read_objects(app, file->buf + offset);
	destroy_file_contents(file);
	ft_printf("Loaded map: %s\nNum objects %u\n", filename, num_objects);
}
