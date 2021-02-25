/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:52 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/22 21:54:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

char		*get_object_texture_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_textures, obj->id));
}

char		*get_object_normal_map_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_normal_maps, obj->id));
}

static void	write_obj_content(int32_t fd, t_doom3d *app, t_3d_object *obj)
{
	int32_t			i;
	char			*texture_file;
	char			*normal_map_file;
	int32_t			len;
	int32_t			ret;

	// !Write the object as is (shallow, (has pointers))
	ret = write(fd, obj, sizeof(t_3d_object));
	// !Write the vertices
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		ret = write(fd, obj->vertices[i], sizeof(t_vertex));
	// !Write the triangles
	i = -1;
	while (++i < (int32_t)obj->num_triangles)
		ret = write(fd, &obj->triangles[i], sizeof(t_triangle));
	// !Write the texture & normal maps filenames, and the length of those strs
	texture_file = get_object_texture_filename(app->active_scene, obj);
	len = ft_strlen(texture_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, texture_file, len);
	normal_map_file = get_object_normal_map_filename(app->active_scene, obj);
	len = ft_strlen(normal_map_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, normal_map_file, len);
	// !Write the shading opts
	ret = write(fd, &obj->material->shading_opts, sizeof(uint32_t));
	(void)ret;
}

/*
** For each object_type_path, writes the id of the object, num of neighbors
** and each neighbor id for the purpose of saving the connections
*/

static void	write_path_object_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_path_node	*path_node;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_path)
		{
			path_node = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &path_node->num_neighbors, sizeof(int32_t));
			j = -1;
			while (++j < path_node->num_neighbors)
				ret = write(fd, &path_node->neighbors[j]->id, sizeof(uint32_t));
		}
	}
	(void)ret;
}

/*
** Writes patrol path info
** of npcs that might have them
*/

static void	write_npc_patrol_path_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_npc		*npc;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_npc)
		{
			npc = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &npc->num_patrol_path_nodes, sizeof(int32_t));
			j = -1;
			while (++j < npc->num_patrol_path_nodes)
				if (npc->patrol_path[j])
					ret = write(fd, &npc->patrol_path[j]->id, sizeof(uint32_t));
				else
					ret = write(fd, 0, sizeof(uint32_t));
		}
	}
	(void)ret;
}

/*
** Writes trigger links
** of triggers that might have them
*/

static void	write_trigger_link_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_trigger	*trigger;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_trigger)
		{
			trigger = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &trigger->num_links, sizeof(int32_t));
			j = -1;
			while (++j < trigger->num_links)
				if (trigger->linked_obj[j])
					ret = write(fd, &trigger->linked_obj[j]->id, sizeof(uint32_t));
				else
					ret = write(fd, 0, sizeof(uint32_t));
		}
	}
	(void)ret;
}

static void	write_map(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		ret;

	ret = write(fd, "MAP\0", 4);
	ret = write(fd, &app->active_scene->num_objects, sizeof(uint32_t));
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			write_obj_content(fd, app, app->active_scene->objects[i]);
	write_path_object_information(fd, app);
	write_npc_patrol_path_information(fd, app);
	write_trigger_link_information(fd, app);
	(void)ret;
}

void		save_map(t_doom3d *app)
{
	int32_t			fd;
	char			filename[128];

	ft_sprintf(filename, "assets/map_data/%s",
		app->editor.editor_filename, app->editor.editor_filename);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write_map(fd, app);
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
}
