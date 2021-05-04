/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:52 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:35:06 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Write object content in bytes (Order is Important!)
** 1. Write object as is (shallow copy, so pointers will point to nothing)
** 2. Write vertices
** 3. Write triangles
** 4. Write texture & normal map filenames and their lengths
** 5. Write shading opts
*/

static void	write_obj_content(int32_t fd, t_doom3d *app, t_3d_object *obj)
{
	int32_t			i;
	char			*texture_file;
	char			*normal_map_file;
	int32_t			len;
	int32_t			ret;

	ret = write(fd, obj, sizeof(t_3d_object));
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		ret = write(fd, obj->vertices[i], sizeof(t_vertex));
	i = -1;
	while (++i < (int32_t)obj->num_triangles)
		ret = write(fd, &obj->triangles[i], sizeof(t_triangle));
	texture_file = get_object_texture_filename(app->active_scene, obj);
	len = ft_strlen(texture_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, texture_file, len);
	normal_map_file = get_object_normal_map_filename(app->active_scene, obj);
	len = ft_strlen(normal_map_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, normal_map_file, len);
	ret = write(fd, &obj->material->shading_opts, sizeof(uint32_t));
	(void)ret;
}

static void	write_map(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		ret;

	ret = write(fd, "MAP\0", 4);
	ret = write(fd, &app->active_scene->num_objects, sizeof(uint32_t));
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			write_obj_content(fd, app, app->active_scene->objects[i]);
	write_path_object_information(fd, app);
	write_npc_patrol_path_information(fd, app);
	write_trigger_link_information(fd, app);
	write_key_ids(fd, app);
	(void)ret;
}

/*
** Save map file writing ordered binary data onto `editor_filename` named
** file
*/

void	save_map(t_doom3d *app)
{
	int32_t			fd;
	char			filename[128];
	int32_t			i;
	t_bool			is_new;

	remove_all_objects_shading_opts(app, e_shading_lit);
	ft_sprintf(filename, "assets/map_data/%s", app->editor.editor_filename);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1
		&& ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write_map(fd, app);
	fd = close(fd);
	if (fd == -1
		&& ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
	is_new = true;
	i = -1;
	while (++i < MAX_LEVELS)
	{
		if (ft_strequ(app->level_list[i], app->editor.editor_filename))
			is_new = false;
	}
	if (is_new)
		write_savename_to_level_list(app);
}
