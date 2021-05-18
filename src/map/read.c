/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/18 22:09:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static uint32_t	get_asset_map_offset(t_file_contents *file)
{
	char			map_header[8];
	uint32_t		offset;
	uint32_t		assets_size;

	ft_memcpy(&map_header, file->buf, 8);
	offset = 8;
	if (!ft_strequ(map_header, "ASSETS\0"))
		error_check(true, "Invalid map. First map must start ASSETS\0");
	ft_memcpy(&assets_size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	offset += assets_size;
	LOG_INFO("Reading first level, skip assets by offset %d", assets_size);
	ft_memcpy(&map_header, file->buf + offset, 4);
	offset += 4;
	LOG_INFO("Map header: %s", map_header);
	if (!ft_strequ(map_header, "MAP\0"))
		error_check(true, "Invalid map file. First 4 bytes must be MAP\0");
	return (offset);
}

static uint32_t	get_initial_offset(t_doom3d *app, t_file_contents *file,
					const char *map_name)
{
	char			map_header[4];
	uint32_t		offset;

	if (!((app->current_level == 0 && ft_strequ(FIRST_LEVEL, map_name))
		|| (app->editor.editor_level == 0 && ft_strequ(FIRST_LEVEL, map_name))))
	{
		offset = 4;
		ft_memcpy(&map_header, file->buf, 4);
		if (!ft_strequ(map_header, "MAP\0"))
			error_check(true, "Invalid map file. First 4 bytes must be MAP\0");
	}
	else
		offset = get_asset_map_offset(file);
	return (offset);
}

static uint32_t	validate_map_file(t_doom3d *app,
					t_file_contents *file, const char *map_name,
					char *filename)
{
	if (!map_name)
	{
		LOG_FATAL("Map filename %s, ensure the level_list.txt has a map name",
			map_name);
		exit(EXIT_FAILURE);
	}
	if (!file)
	{
		LOG_FATAL("Failed to read %s, check assets/map_data/", filename);
		exit(EXIT_FAILURE);
	}
	return (get_initial_offset(app, file, map_name));
}

/*
** Read map data onto active scene from char *map_name file
*/

void	read_map(t_doom3d *app, const char *map_name)
{
	t_file_contents	*file;
	char			filename[128];
	int32_t			offset;

	ft_sprintf(filename, "assets/map_data/%s", map_name);
	LOG_INFO("Read map %s", filename);
	file = read_file(filename);
	offset = validate_map_file(app, file, map_name, filename);
	ft_memcpy(&app->active_scene->num_objects,
		file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	offset += read_objects(app, file->buf + offset);
	offset += read_path_nodes(app, file->buf + offset);
	offset += read_path_node_npc_links(app, file->buf + offset);
	offset += read_trigger_link_information(app, file->buf + offset);
	offset += read_key_id_information(app, file->buf + offset);
	destroy_file_contents(file);
}
