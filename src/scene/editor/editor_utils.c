/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/21 19:59:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

uint32_t	random_uuid(void)
{
	return (rand());
}

char		*get_object_texture_filename(t_scene *scene, t_3d_object *obj)
{
	int32_t		i;
	t_surface	*texture;

	if (obj->material->texture == NULL)
		return (NULL);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_keys)
	{
		texture =
			hash_map_get(scene->textures, scene->asset_files.asset_keys[i]);
		if (texture == obj->material->texture)
			return (hash_map_get(scene->asset_files.texture_files,
				scene->asset_files.asset_keys[i]));
	}
	return (NULL);
}

char		*get_object_normal_map_filename(t_scene *scene, t_3d_object *obj)
{
	int32_t		i;
	t_surface	*texture;

	if (obj->material->texture == NULL)
		return (NULL);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_keys)
	{
		texture =
			hash_map_get(scene->normal_maps, scene->asset_files.asset_keys[i]);
		if (texture == obj->material->normal_map)
			return (hash_map_get(scene->asset_files.normal_map_files,
				scene->asset_files.asset_keys[i]));
	}
	return (NULL);
}

void		write_obj_content(t_doom3d *app, t_3d_object *obj)
{
	int32_t			fd;
	char			filename[128];
	int32_t			i;
	char			refs[128];

	ft_sprintf(filename, "map_data/%s/%s.bin", app->editor_filename, obj->id);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write(fd, obj, sizeof(t_3d_object));
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		write(fd, obj->vertices[i], sizeof(t_vertex));
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
	ft_sprintf(filename, "map_data/%s/%s.txt", app->editor_filename, obj->id);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	ft_sprintf(refs, "%s\n%s\n",
		get_object_texture_filename(app->active_scene, obj),
		get_object_normal_map_filename(app->active_scene, obj));
	write(fd, refs, ft_strlen(refs));
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
}

void		write_map_composition(int32_t fd, t_doom3d *app)
{
	t_map_file	map_file;
	int32_t		i;


	ft_memcpy(map_file.header, "MAP\0", 4);
	map_file.num_objects = app->active_scene->num_objects;
	i = -1;
	while (++i < (int32_t)map_file.num_objects)
	{
		map_file.object_ids[i] = app->active_scene->objects[i]->id;
		write_obj_content(app, app->active_scene->objects[i]);
	}
	write(fd, &map_file, sizeof(map_file));
}

void		save_map(t_doom3d *app)
{
	int32_t			fd;
	char			dirname[64];
	char			filename[128];

	ft_sprintf(dirname, "map_data/%s", app->editor_filename);
	if(mkdir(dirname, 0777) && errno != EEXIST)
	{
		ft_dprintf(2, "Error when trying to create '%s'\n", dirname);
		exit(EXIT_FAILURE);
	}
	ft_sprintf(filename, "map_data/%s/%s.data",
		app->editor_filename, app->editor_filename);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write_map_composition(fd, app);
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
}
