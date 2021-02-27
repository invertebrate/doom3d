/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 15:51:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				player_rotation_handle(t_doom3d *app,
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
	player_rotation_handle(app, xrel, yrel);
	if (!app->player.is_shooting && (app->mouse.state & SDL_BUTTON_LMASK))
		app->player.is_shooting = true;
	else if (!(app->mouse.state & SDL_BUTTON_LMASK))
	{
		app->player.is_shooting = false;
		set_player_default_frame(app);
	}
	if (app->player.is_shooting)
	{
		player_shoot(app, SDL_GetTicks());
	}
}

static void				object_rotation_handle(t_doom3d *app,
							int32_t xrel, int32_t yrel)
{
	static uint32_t		last_rotated;
	uint32_t			diff;
	float				angle;

	if (app->editor.num_selected_objects != 1)
		return ;
	diff = SDL_GetTicks() - last_rotated;
	if (app->keyboard.state[SDL_SCANCODE_Q] && diff > 50 && ft_abs(xrel) > 2)
	{
		angle = (xrel > 0 ? 1 : -1) * 10;
		l3d_3d_object_rotate(app->editor.selected_objects[0],
			 0, angle, 0);
		last_rotated = SDL_GetTicks();
		if (app->editor.selected_objects[0]->type == object_type_npc)
			((t_npc*)app->editor.selected_objects[0]->params)->angle += angle;
		after_editor_transform(app, &last_rotated);
	}
	else if (diff > 50 && ft_abs(xrel) > 2 && ft_abs(yrel) < 8)
	{
		l3d_3d_object_rotate(app->editor.selected_objects[0],
			 0, 0, (xrel > 0 ? 1 : -1) * 10);
		last_rotated = SDL_GetTicks();
		after_editor_transform(app, &last_rotated);
	}
	else if (diff > 50 && ft_abs(yrel) > 2 && ft_abs(xrel) < 8)
	{
		l3d_3d_object_rotate(app->editor.selected_objects[0],
			(yrel > 0 ? 1 : -1) * 10, 0, 0);
		last_rotated = SDL_GetTicks();
		app->editor.is_saved = false;
		after_editor_transform(app, &last_rotated);
	}
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
		player_rotation_handle(app, xrel, yrel);
	}
	else
	{
		app->editor.is_moving = false;
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
		if (app->editor.num_selected_objects == 1 &&
			((app->mouse.state & SDL_BUTTON_MIDDLE) ||
				(app->keyboard.state[SDL_SCANCODE_R])))
		{
			object_rotation_handle(app, xrel, yrel);
		}
	}
}

void					mouse_state_handle(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		mouse_game_state_handle(app);
	if (app->active_scene->scene_id == scene_id_editor3d &&
		!editor_popup_menu_open(app))
	{
		mouse_editor_state_handle(app);
	}
}
