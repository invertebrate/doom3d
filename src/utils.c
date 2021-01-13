/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/13 16:05:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			doom3d_debug_info_render(t_doom3d *app)
{
	char	debug_info[1024];
	char	pos[128];
	t_vec3	unit_pos;

	if (app->active_scene->scene_id == scene_id_main_game ||
		app->active_scene->scene_id == scene_id_editor3d)
	{
		ml_vector3_mul(app->player.pos, 1.0 / app->unit_size, unit_pos);
		ml_vector3_to_str(unit_pos, pos);
		ft_sprintf(debug_info, "fps: %u\ndelta time: %u\nunit_pos: %s",
			app->info.fps, app->info.delta_time, pos);
	}
	else
		ft_sprintf(debug_info, "fps: %u\ndelta time: %u",
			app->info.fps, app->info.delta_time);
	window_text_render_wrapped(app->window, (t_text_params){
		.text = debug_info, .blend_ratio = 1.0, .xy = (int[2]){5, 5},
		.text_color = (SDL_Color){255, 255, 255, 0}},
		app->window->debug_font, app->window->framebuffer->width);
}

void			doom3d_debug_info_capture(t_doom3d *app)
{
	app->info.performance_end = SDL_GetPerformanceCounter();
	app->info.delta_time =
		(app->info.performance_end - app->info.performance_start) * 1000.0 /
		SDL_GetPerformanceFrequency();
	app->info.fps = window_framerate_capture(app->info.delta_time);
}

uint64_t		doom3d_performance_counter_start(void)
{
	return (SDL_GetPerformanceCounter());
}

void			doom3d_performance_counter_end(uint64_t start_time,
					char *task_name, float delta_limit)
{
	float			delta_time;

	delta_time = (float)(SDL_GetPerformanceCounter() -
		start_time) * 1000.0 /
		(float)SDL_GetPerformanceFrequency();
	if (delta_limit == 0.0 || delta_time > delta_limit)
		ft_printf("%s: Profiler time: %f\n", task_name, delta_time);
}

void			doom3d_notifications_update(t_doom3d *app)
{
	t_notification	*last_notification;
	t_list			**last_node;

	last_node = &app->notifications;
	if (!*last_node)
		return ;
	while ((*last_node)->next)
		last_node = &(*last_node)->next;
	last_notification = (*last_node)->content;
	last_notification->time -= app->info.delta_time;
	if (last_notification->time <= 0)
	{
		free(last_notification);
		free(*last_node);
		*last_node = NULL;
	}
}

void			doom3d_notification_add(t_doom3d *app,
					t_notification notification)
{
	if (app->notifications == NULL)
		app->notifications = ft_lstnew(&notification, sizeof(t_notification));
	else
		ft_lstadd(&app->notifications,
			ft_lstnew(&notification, sizeof(t_notification)));
}

void			doom3d_notifications_delete_all(t_doom3d *app)
{
	t_list		*node;
	t_list		*tmp;

	node = app->notifications;
	while (node)
	{
		tmp = node;
		free((t_notification*)node->content);
		node = node->next;
		free(tmp);
	}
	app->notifications = NULL;
}