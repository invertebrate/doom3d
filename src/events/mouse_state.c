/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/29 14:47:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				mouse_motion_handle(t_doom3d *app,
							int32_t xrel, int32_t yrel)
{
	if (xrel != 0 || yrel != 0)
	{
		app->player.is_rotating = true;
		player_rotate_vertical(app, -(float)yrel * 0.3);
		player_rotate_horizontal(app, (float)xrel * 0.3);
	}
	else
		app->player.is_rotating = false;
}

static void				mouse_game_state_handle(t_doom3d *app)
{
	int32_t	xrel;
	int32_t	yrel;

	SDL_GetRelativeMouseState(&xrel, &yrel);
	mouse_motion_handle(app, xrel, yrel);
	if (!app->player.is_shooting && (app->mouse.state & SDL_BUTTON_LMASK))
	{
		app->player.is_shooting = true;
		player_shoot(app, SDL_GetTicks());
	}
	else if (!(app->mouse.state & SDL_BUTTON_LMASK))
	{
		app->player.is_shooting = false;
	}
	if (app->player.is_shooting)
		player_shoot(app, SDL_GetTicks());
}

static void				mouse_editor_state_handle(t_doom3d *app)
{
	int32_t	xrel;
	int32_t	yrel;

	if ((app->mouse.state & SDL_BUTTON_RMASK))
	{
		app->editor.is_moving = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
		mouse_motion_handle(app, xrel, yrel);
	}
	else
	{
		app->editor.is_moving = false;
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
	}
}

void					mouse_state_handle(t_doom3d *app)
{
	app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		mouse_game_state_handle(app);
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		mouse_editor_state_handle(app);
	}
}
