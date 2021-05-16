/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_duplication.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:26:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 00:47:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	is_start_or_end_object(t_3d_object *selected)
{
	return ((selected->type == object_type_trigger
			&& selected->params_type == trigger_player_start)
		|| (selected->type == object_type_trigger
			&& selected->params_type == trigger_player_end));
}

/*
** Copy object, descale it, detransform and place scene object (which will
** scale by unit size)
*/

static void	duplicate_scene_object(t_doom3d *app, t_3d_object *selected)
{
	t_3d_object	*model;
	const char	*texture_file;
	const char	*normal_map_file;

	texture_file = NULL;
	if (selected->material->texture)
		texture_file = selected->material->texture->filename;
	normal_map_file = NULL;
	if (selected->material->normal_map)
		normal_map_file =  selected->material->normal_map->filename;
	model = l3d_3d_object_copy(selected);
	l3d_3d_object_scale(model,
		1.0 / app->unit_size, 1.0 / app->unit_size, 1.0 / app->unit_size);
	l3d_3d_object_translate(model, -selected->position[0],
		-selected->position[1], -selected->position[2]);
	place_procedural_scene_object(app, model,
		(const char*[2]){texture_file, normal_map_file},
		(t_vec3){selected->position[0], selected->position[1],
		selected->position[2] + -app->unit_size});
	l3d_3d_object_destroy(model);
}

/*
** Duplicate selected object
*/

static void	duplicate_selected_object(t_doom3d *app, t_3d_object *selected)
{
	t_bool		start_or_end;

	start_or_end = is_start_or_end_object(selected);
	if (!start_or_end)
	{
		duplicate_scene_object(app, selected);
		app->active_scene->objects[
			app->active_scene->last_object_index]->material->shading_opts
			= selected->material->shading_opts;
		select_object(app,
			app->active_scene->objects[app->active_scene->last_object_index]);
		notify_user(app, (t_notification){
			.message = "Duplicated an object!", .time = 2000,
			.type = notification_type_info});
	}
	else if (start_or_end)
		notify_user(app, (t_notification){
			.message = "Can't duplicate start or end triggers!", .time = 2000,
			.type = notification_type_info});
}

/*
** Duplicates and selects any object that is not start or end trigger
** Uses existing object placement functionality from place scene object
** thus we need to once reset the scale by 1.0 / app->unit_size
** and inverse translate.
*/

void	editor_duplicate_selected_objects(t_doom3d *app)
{
	int32_t		i;
	t_3d_object	*old_selected[MAX_SELECTED_OBJECTS];
	int32_t		num_selected;

	if (app->editor.num_selected_objects == 0)
	{
		notify_user(app, (t_notification){
			.message = "Select an object first for duplication!", .time = 2000,
			.type = notification_type_info});
		return ;
	}
	num_selected = app->editor.num_selected_objects;
	i = -1;
	while (++i < num_selected)
		old_selected[i] = app->editor.selected_objects[i];
	editor_deselect_all(app);
	i = -1;
	while (++i < num_selected)
		duplicate_selected_object(app, old_selected[i]);
}
