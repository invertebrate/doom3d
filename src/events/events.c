/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 15:40:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool			editor_popup_menu_open(t_doom3d *app)
{
	return (app->editor.editor_menu != NULL &&
			app->editor.editor_menu->is_open);
}

static void		editor_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		handle_editor_saving(app, event);
		handle_editor_selection(app, event);
	}
	if (event.type == SDL_MOUSEWHEEL)
	{
		editor_vertical_move(app, -event.wheel.y * 30);
	}
}

static void		doom3d_button_events_handle(t_doom3d *app, SDL_Event event)
{
	int32_t	i;

	if (editor_popup_menu_open(app))
	{
		button_popup_menu_events_handle(app->editor.editor_menu,
			app->mouse, event);
		return ;
	}
	if ((app->active_scene->scene_id != scene_id_main_game) ||
			(app->active_scene->scene_id == scene_id_main_game &&
				app->active_scene->is_paused))
	{
		if (app->active_scene->scene_id == scene_id_editor3d &&
			app->editor.is_moving)
			return ;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_button_menus)
			button_group_events_handle(app->active_scene->menus[i],
				app->mouse, event);
	}
}

void			doom3d_game_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		player_jump(app);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_9)
	{
		app->player.can_fly = (app->player.can_fly + 1) % 2;
		ft_printf("player can fly = %d\n", app->player.can_fly);//test
	}
}

void			input_events_handle(t_doom3d *app, SDL_Event event)
{
	general_input_events_handle(app, event);
	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		doom3d_game_input_events_handle(app, event);
	if (app->active_scene->scene_id == scene_id_editor3d &&
		!editor_popup_menu_open(app))
		editor_input_events_handle(app, event);
	doom3d_button_events_handle(app, event);
}

void			events_handle(t_doom3d *app)
{
	SDL_Event	event;

	SDL_PumpEvents();
	app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
	app->keyboard.state = SDL_GetKeyboardState(NULL);
	if (!app->active_scene->is_paused)
	{
		mouse_state_handle(app);
		keyboard_state_handle(app);
	}
	while (SDL_PollEvent(&event))
	{
		if (event.type == app->custom_event_type)
			doom3d_events_handle(app, event);
		else
			input_events_handle(app, event);
	}
}
