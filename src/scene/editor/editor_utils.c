/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/01 20:50:26 by ohakola          ###   ########.fr       */
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

void		editor_objects_invisible_highlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj)
		{
			if (obj->type == object_type_trigger ||
				obj->type == object_type_light ||
				obj->type == object_type_path)
			{
				obj->material->shading_opts = (obj->material->shading_opts &
					~(e_shading_invisible));
				if (obj->params_type == trigger_player_start)
					obj->material->shading_opts = e_shading_green;
				if (obj->params_type == trigger_player_end)
					obj->material->shading_opts = e_shading_red;
				if (obj->params_type == object_type_light)
					obj->material->shading_opts = e_shading_yellow;
				if (obj->params_type == object_type_path)
					obj->material->shading_opts = e_shading_cyan;
			}
		}
	}
}

void		editor_objects_invisible_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj &&
			((obj->type == object_type_trigger &&
				(obj->params_type == trigger_player_start ||
				obj->params_type == trigger_player_end)) ||
				obj->type == object_type_light ||
				obj->type == object_type_path))
			obj->material->shading_opts = e_shading_invisible;
	}
}