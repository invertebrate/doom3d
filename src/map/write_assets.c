/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 19:10:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	log_containing_asset_filenames(void *val, void *params)
{
	const char	*filename;
	t_doom3d	*app;

	app = params;
	(void)app;
	filename = val;
	LOG_INFO("Textures on objects: %s", filename);
}

void	write_assets(int32_t fd, t_doom3d *app)
{
	(void)fd;
	hash_map_foreach(app->active_scene->object_textures,
		log_containing_asset_filenames, app);
}
