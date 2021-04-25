/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:10:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:46:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Read map data onto active scene from char *map_name file
*/

void			read_map(t_doom3d *app, const char *map_name)
{
	t_file_contents	*file;
	char			filename[128];
	char			header[4];
	int32_t			offset;

	ft_sprintf(filename, "assets/map_data/%s", map_name);
	LOG_INFO("Read map %s", filename);
	file = read_file(filename);
	if (!file)
	{
		LOG_INFO("Failed to read map %s", filename);
		exit(EXIT_FAILURE);
	}
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
