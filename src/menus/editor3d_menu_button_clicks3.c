/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_button_clicks3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:18:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 16:18:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	on_normmaps_menu_button_click(t_button *self, void *params)
{
	push_custom_event(params, event_editor_add_normal_map, (void *)self->text,
		NULL);
}

void	on_npc_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	push_custom_event(app, event_editor_start_placement,
		(void *)object_type_npc, hash_map_get(app->active_scene->npc_map,
			(int64_t)self->text));
}

void	on_prefab_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	push_custom_event(app, event_editor_start_placement,
		(void *)object_type_default,
		hash_map_get(app->active_scene->prefab_map,
			(int64_t)self->text));
}

void	on_trigger_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
			(int64_t)self->text);
	push_custom_event(app, event_editor_start_placement,
		(void *)object_type_trigger, get_res);
}

void	on_light_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
			(int64_t)self->text);
	push_custom_event(app, event_editor_start_placement,
		(void *)object_type_light, get_res);
}
