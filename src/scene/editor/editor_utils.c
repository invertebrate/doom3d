/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 15:32:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static char	*get_object_texture_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_textures, obj->id));
}

static char	*get_object_normal_map_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_normal_maps, obj->id));
}

static void	write_obj_content(int32_t fd, t_doom3d *app, t_3d_object *obj)
{
	int32_t			i;
	char			*texture_file;
	char			*normal_map_file;
	int32_t			len;

	// !Write the object as is (shallow, (has pointers))
	write(fd, obj, sizeof(t_3d_object));
	// !Write the vertices
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		write(fd, obj->vertices[i], sizeof(t_vertex));
	// !Write the triangles
	i = -1;
	while (++i < (int32_t)obj->num_triangles)
		write(fd, &obj->triangles[i], sizeof(t_triangle));
	// !Write the texture & normal maps filenames, and the length of those strs
	texture_file = get_object_texture_filename(app->active_scene, obj);
	len = ft_strlen(texture_file);
	write(fd, &len, sizeof(uint32_t));
	write(fd, texture_file, len);
	normal_map_file = get_object_normal_map_filename(app->active_scene, obj);
	len = ft_strlen(normal_map_file);
	write(fd, &len, sizeof(uint32_t));
	write(fd, normal_map_file, len);
}

static void	write_map(int32_t fd, t_doom3d *app)
{
	int32_t		i;

	write(fd, "MAP\0", 4);
	write(fd, &app->active_scene->num_objects, sizeof(uint32_t));
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		write_obj_content(fd, app, app->active_scene->objects[i]);
}

void		save_map(t_doom3d *app)
{
	int32_t			fd;
	char			filename[128];

	ft_sprintf(filename, "assets/map_data/%s.data",
		app->editor_filename, app->editor_filename);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write_map(fd, app);
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
}

const char	*texture_file_key(char *filename, t_doom3d *app)
{
	int32_t		i;

	ft_printf("%s\n", filename);
	i = -1;
	while (++i < (int32_t)app->active_scene->asset_files.num_textures)
	{
		if (ft_strequ(filename,
			app->active_scene->asset_files.texture_files[i]))
			return (app->active_scene->asset_files.texture_files[i]);
	}
	return (NULL);
}

const char	*normal_map_file_key(char *filename, t_doom3d *app)
{
	int32_t		i;

	ft_printf("%s\n", filename);
	i = -1;
	while (++i < (int32_t)app->active_scene->asset_files.num_normal_maps)
	{
		if (ft_strequ(filename,
			app->active_scene->asset_files.normal_map_files[i]))
			return (app->active_scene->asset_files.texture_files[i]);
	}
	return (NULL);
}

static int32_t	read_obj_texture(t_3d_object *obj,
					t_doom3d *app, char *contents)
{
	int32_t		len;
	int32_t		offset;
	char		buf[128];
	const char	*filename;

	ft_memcpy(&len, contents, sizeof(uint32_t));
	ft_printf("Len: %d\n", len);
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
	ft_printf("Len: %d\n", len);
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
		ft_printf("Managed to copy obj %u\n", obj->num_vertices);
		j = -1;
		while (++j < (int32_t)obj->num_vertices)
		{
			ft_printf("Copy vertex %d\n", j);
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
	ft_printf("Num objects %u\n", num_objects);
	read_objects(app, file->buf + offset);
	destroy_file_contents(file);
}
