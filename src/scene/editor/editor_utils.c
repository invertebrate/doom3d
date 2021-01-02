/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 18:29:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

const char	*texture_file_key(char *filename, t_doom3d *app)
{
	int32_t		i;

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

	i = -1;
	while (++i < (int32_t)app->active_scene->asset_files.num_normal_maps)
	{
		if (ft_strequ(filename,
			app->active_scene->asset_files.normal_map_files[i]))
			return (app->active_scene->asset_files.texture_files[i]);
	}
	return (NULL);
}

void		after_editor_transform(t_doom3d *app, uint32_t *last_changed)
{
	app->editor.is_saved = false;
	*last_changed = SDL_GetTicks();
	active_scene_update_after_objects(app->active_scene);
}
