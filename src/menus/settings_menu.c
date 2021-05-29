/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:41:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 20:01:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	on_settings_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		push_custom_event(app, event_window_resize, (void *)960, (void *)540);
	else if (self->id == 1)
		push_custom_event(app, event_window_resize, (void *)1280, (void *)720);
	else if (self->id == 2)
		push_custom_event(app, event_window_resize, (void *)1920, (void *)1080);
	else if (self->id == 3)
		push_custom_event(app, event_scene_change,
			(void*)scene_id_main_menu, NULL);
}

static void	on_difficulty_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		push_custom_event(app, event_set_difficulty,
			(void *)(intptr_t)self->id, NULL);
	else if (self->id == 1)
		push_custom_event(app, event_set_difficulty,
			(void *)(intptr_t)self->id, NULL);
}

static void	on_level_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	push_custom_event(app, event_select_level,
		(void *)(intptr_t)self->id, NULL);
}

static void	update_settings_selectors(t_doom3d *app)
{
	SDL_Event	dummy;

	if (app->settings.width == 960)
		button_group_set_selector(app->active_scene->menus[0], 0);
	else if (app->settings.width == 1280)
		button_group_set_selector(app->active_scene->menus[0], 1);
	else if (app->settings.width == 1920)
		button_group_set_selector(app->active_scene->menus[0], 2);
	if (app->settings.is_hard)
		button_group_set_selector(app->active_scene->menus[1], 1);
	else
		button_group_set_selector(app->active_scene->menus[1], 0);
	button_group_set_selector(app->active_scene->menus[2], app->current_level);
	ft_memset(&dummy, 0, sizeof(dummy));
	dummy.type = SDL_MOUSEBUTTONUP;
	dummy.button.button = SDL_BUTTON_MMASK;
	button_group_events_handle(app->active_scene->menus[0], app->mouse, dummy);
	button_group_events_handle(app->active_scene->menus[1], app->mouse, dummy);
	button_group_events_handle(app->active_scene->menus[2], app->mouse, dummy);
}

/*
** Create settings menu
*/

void	settings_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus
			= ft_calloc(sizeof(t_button_group*) * 3)),
		"Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create_shaded(app,
			(t_button_menu_params){.button_names = (const char*[4]){
			"Small", "Medium", "Large", "Back"},
			.num_buttons = 4, .on_click = on_settings_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[1] = button_menu_create_shaded(app,
			(t_button_menu_params){
			.button_names = (const char*[4]){"Normal", "Hard"},
			.num_buttons = 2, .on_click = on_difficulty_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[2] = button_menu_create_shaded(app,
			(t_button_menu_params){
			.button_names = (const char **)app->level_list,
			.num_buttons = app->num_levels,
			.on_click = on_level_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 3;
	update_settings_selectors(app);
}
