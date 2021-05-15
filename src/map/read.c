/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 16:26:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	validate_map_file(t_file_contents *file, const char *map_name,
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
}

/*
** Read map data onto active scene from char *map_name file
*/

void	read_map(t_doom3d *app, const char *map_name)
{
	t_file_contents	*file;
	char			filename[128];
	char			header[4];
	int32_t			offset;

	ft_sprintf(filename, "assets/map_data/%s", map_name);
	LOG_INFO("Read map %s", filename);
	file = read_file(filename);
	validate_map_file(file, map_name, filename);
	ft_memcpy(&header, file->buf, (offset = 4));
	if (!ft_strequ(header, "MAP\0"))
		error_check(true, "Invalid map file. First 4 bytes must be MAP\0");
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
