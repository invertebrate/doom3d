/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:10:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:11:24 by ohakola          ###   ########.fr       */
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
	// Write size of all assets first.
	// Write assets in one big blob here. Write filenames, write sizes etc.
	(void)fd;
	hash_map_foreach(app->active_scene->object_textures,
		log_containing_asset_filenames, app);
}