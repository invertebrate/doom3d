/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_button_clicks3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:18:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 03:19:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			on_normmaps_menu_button_click(t_button *self, void *params)
{
	doom3d_push_event(params, event_editor_add_normal_map, (void*)self->text,
		NULL);
}

void			on_npc_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	doom3d_push_event(app, event_editor_start_placement,
		(void*)object_type_npc, hash_map_get(app->active_scene->npc_map,
		(int64_t)self->text));
}

void			on_prefab_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_default,
			hash_map_get(app->active_scene->prefab_map,
		(int64_t)self->text));
}

void			on_trigger_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
		(int64_t)self->text);
	doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, get_res);
}

void			on_light_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	(void)self;
	app = params;
	doom3d_push_event(app, event_editor_start_placement,
		(void*)object_type_light, NULL);
}
