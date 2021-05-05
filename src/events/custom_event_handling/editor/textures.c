/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:43:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:23:02 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Adds given normal map to selected object (if any)
*/

void	handle_editor_add_normal_map(t_doom3d *app, char *filename)
{
	int32_t		i;
	t_surface	*normmap;

	if (app->editor.num_selected_objects > 0)
	{
		normmap
			= hash_map_get(app->active_scene->normal_maps, (int64_t)filename);
		i = -1;
		while (++i < app->editor.num_selected_objects)
		{
			app->editor.selected_objects[i]->material->normal_map = normmap;
			hash_map_add(app->active_scene->object_normal_maps,
				app->editor.selected_objects[i]->id, (void *)filename);
		}
		app->editor.is_saved = false;
		notify_user(app, (t_notification){
			.message = "Normal map set!",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		notify_user(app, (t_notification){
			.message = "Select object first!",
			.type = notification_type_info, .time = 2000});
	}
}

/*
** Adds given texture to selected object (if any)
*/

void	handle_editor_add_texture(t_doom3d *app, char *filename)
{
	int32_t		i;
	t_surface	*texture;

	if (app->editor.num_selected_objects > 0)
	{
		texture
			= hash_map_get(app->active_scene->textures, (int64_t)filename);
		i = -1;
		while (++i < app->editor.num_selected_objects)
		{
			app->editor.selected_objects[i]->material->texture = texture;
			hash_map_add(app->active_scene->object_textures,
				app->editor.selected_objects[i]->id, (void*)filename);
		}
		app->editor.is_saved = false;
		notify_user(app, (t_notification){
			.message = "Texture set!",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		notify_user(app, (t_notification){
			.message = "Select object first!",
			.type = notification_type_info, .time = 2000});
	}
}
