/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 17:30:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		menu_options_handle(t_doom3d *app, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		app->active_scene->selected_option--;
	else if (event.key.keysym.sym == SDLK_DOWN)
		app->active_scene->selected_option++;
	if (app->active_scene->selected_option >=
		app->active_scene->menu_option_count)
		app->active_scene->selected_option = 0;
	if (app->active_scene->selected_option < 0)
		app->active_scene->selected_option =
			app->active_scene->menu_option_count - 1;
}

void			main_menu_event_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		menu_options_handle(app, event);
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			if (app->active_scene->selected_option == 0)
			{
				app->next_scene_id = scene_id_main_game;
				scene_next_select(app);
			}
			else if (app->active_scene->selected_option == 1)
			{
				app->next_scene_id = scene_id_main_menu_settings;
				scene_next_select(app);
			}
			else if (app->active_scene->selected_option == 2)
				app->is_running = false;
		}
	}
}

void			main_menu_settings_event_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		menu_options_handle(app, event);
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			if (app->active_scene->selected_option == 0)
				window_resize(app->window, 960, 540);
			else if (app->active_scene->selected_option == 1)
				window_resize(app->window, 1280, 720);
			else if (app->active_scene->selected_option == 2)
				window_resize(app->window, 1920, 1080);
			else if (app->active_scene->selected_option == 3)
			{
				app->next_scene_id = scene_id_main_menu;
				scene_next_select(app);
			}
		}
	}
}

void			main_game_menu_event_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		menu_options_handle(app, event);
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			if (app->active_scene->selected_option == 0)
			{
				app->next_scene_id = scene_id_main_menu;
				app->active_scene->is_paused = false;
				scene_next_select(app);
			}
			else if (app->active_scene->selected_option == 1)
				app->is_running = false;
		}
	}
}
