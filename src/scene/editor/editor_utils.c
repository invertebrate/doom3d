/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/22 22:10:54 by ohakola          ###   ########.fr       */
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

/*
** Duplicates and selects any object that is not start or end trigger
** Uses existing object placement functionality from place scene object
** thus we need to once reset the scale by 1.0 / app->unit_size
** and inverse translate.
*/

void			editor_duplicate_selected_object(t_doom3d *app)
{
	t_3d_object	*selected;
	t_3d_object	*model;
	const char	*texture_file;
	const char	*normal_map_file;
	t_bool		start_or_end;

	selected = app->editor.selected_object;
	start_or_end =
		(selected->type == object_type_trigger &&
			selected->params_type == trigger_player_start) || 
		(selected->type == object_type_trigger &&
			selected->params_type == trigger_player_end);
	if (selected && !start_or_end)
	{
		editor_deselect_all(app);
		texture_file = get_object_texture_filename(app->active_scene, selected);
		normal_map_file =
			get_object_normal_map_filename(app->active_scene, selected);
		model = l3d_3d_object_copy(selected);
		// Since we're copying and not selecting from model hash table, descale first
		l3d_3d_object_scale(model,
			1.0 / app->unit_size, 1.0 / app->unit_size, 1.0 / app->unit_size);
		l3d_3d_object_translate(model, -selected->position[0],
			-selected->position[1], -selected->position[2]);
		place_procedural_scene_object(app, model,
			(const char*[2]){texture_file, normal_map_file},
			(t_vec3){selected->position[0], selected->position[1],
			selected->position[2] + -app->unit_size});
		l3d_3d_object_destroy(model);
		// Since place scene object instantiates, we also want to copy shading
		app->active_scene->objects[
			app->active_scene->last_object_index]->material->shading_opts =
				selected->material->shading_opts;
		select_object(app,
			app->active_scene->objects[app->active_scene->last_object_index]);
		doom3d_notification_add(app, (t_notification){
			.message = "Duplicated an object!", .time = 2000,
			.type = notification_type_info});	}
	else if (start_or_end)
		doom3d_notification_add(app, (t_notification){
			.message = "Can't duplicate start or end triggers!", .time = 2000,
			.type = notification_type_info});	
	else
		doom3d_notification_add(app, (t_notification){
			.message = "Select an object first for duplication!", .time = 2000,
			.type = notification_type_info});	
}