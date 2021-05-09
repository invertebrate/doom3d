/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:54:30 by veilo             #+#    #+#             */
/*   Updated: 2021/05/05 17:30:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	finish_level(t_doom3d *app, t_3d_object *end_obj)
{
	end_obj->params_type = trigger_type_disabled;
	app->current_level++;
	if (app->current_level < app->num_levels)
	{
		notify_user(app, (t_notification){
			.message = "New level",
			.type = notification_type_story, .time = 6000});
		push_custom_event(app, event_scene_reload, NULL, NULL);
	}
	else
	{
		app->current_level = 0;
		push_custom_event(app, event_scene_change,
			(void*)scene_id_main_menu, NULL);
		notify_user(app, (t_notification){
			.message = "Game over",
			.type = notification_type_story, .time = 6000});
	}
}
