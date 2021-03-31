/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keyboard_state.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:41:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:37:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		handle_editor_transform(t_doom3d *app)
{
	static uint32_t		last_changed;
	uint32_t			diff;
	int32_t				shift;
	int32_t				i;

	shift = 1;
	if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
		shift = 10;
	diff = SDL_GetTicks() - last_changed;
	if (app->editor.is_saving || app->editor.num_selected_objects == 0)
		return ;
	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		if (diff > 10 && app->keyboard.state[SDL_SCANCODE_UP])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				0, 0, 0.1 * app->unit_size * shift);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 10 && app->keyboard.state[SDL_SCANCODE_RIGHT])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				0.1 * app->unit_size * shift, 0, 0);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 10 && app->keyboard.state[SDL_SCANCODE_DOWN])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				0, 0, -0.1 * app->unit_size * shift);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 10 && app->keyboard.state[SDL_SCANCODE_LEFT])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				-0.1 * app->unit_size * shift, 0, 0);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 10 && app->keyboard.state[SDL_SCANCODE_O])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				0, -0.1 * app->unit_size * shift, 0);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 10 && app->keyboard.state[SDL_SCANCODE_L])
		{
			l3d_3d_object_translate(app->editor.selected_objects[i],
				0, 0.1 * app->unit_size * shift, 0);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 40 && app->keyboard.state[SDL_SCANCODE_LEFTBRACKET])
		{
			l3d_3d_object_scale(app->editor.selected_objects[i],
				1.0 / 1.1, 1.0 / 1.1, 1.0 / 1.1);
			after_editor_transform(app, &last_changed);
		}
		else if (diff > 40 && app->keyboard.state[SDL_SCANCODE_RIGHTBRACKET])
		{
			l3d_3d_object_scale(app->editor.selected_objects[i],
				1.1, 1.1, 1.1);
			after_editor_transform(app, &last_changed);
		}
		l3d_object_aabb_update(app->editor.selected_objects[i]);
	}
}

static void		handle_wasd_movement(t_doom3d *app)
{
	t_vec3	dir;

	if (app->keyboard.state[SDL_SCANCODE_W])
	{
		get_move_dir(app, move_forward, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_A])
	{
		get_move_dir(app, move_strafe_left, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_S])
	{
		get_move_dir(app, move_backward, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_D])
	{
		get_move_dir(app, move_strafe_right, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
}

static t_bool	wasd_is_pressed(t_doom3d *app)
{
	return (app->keyboard.state[SDL_SCANCODE_W] ||
		app->keyboard.state[SDL_SCANCODE_A] ||
		app->keyboard.state[SDL_SCANCODE_S] ||
		app->keyboard.state[SDL_SCANCODE_D]);
}

void			handle_editor_keyboard_state(t_doom3d *app)
{
	handle_wasd_movement(app);
	if (wasd_is_pressed(app))
		app->editor.is_moving = true;
	else
		app->editor.is_moving = false;
	handle_editor_transform(app);
}

t_bool			handle_editor_duplication(t_doom3d *app)
{
	static t_bool	b_down_prev;
	t_bool			b_down;
	t_bool			b_up;
	t_bool			duplicated;

	b_down = app->keyboard.state[SDL_SCANCODE_B];
	b_up = b_down_prev && !b_down;
	duplicated = false;
	if (b_up)
	{
		editor_duplicate_selected_objects(app);
		duplicated = true;
	}
	b_down_prev = b_down;
	return (duplicated);
}