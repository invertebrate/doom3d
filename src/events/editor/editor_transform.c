/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:12:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/04 23:44:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		handle_horizontal_translation(t_doom3d *app, float shift,
					int32_t i, uint32_t *last_changed)
{
	if (app->keyboard.state[SDL_SCANCODE_UP])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			0, 0, 0.1 * app->unit_size * shift);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_RIGHT])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			0.1 * app->unit_size * shift, 0, 0);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_DOWN])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			0, 0, -0.1 * app->unit_size * shift);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_LEFT])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			-0.1 * app->unit_size * shift, 0, 0);
		*last_changed = SDL_GetTicks();
	}
}

static void		handle_object_translation_input(t_doom3d *app,
					int32_t i, uint32_t *last_changed)
{
	float				shift;

	shift = 1.0 * app->info.delta_time * CONST_SPEED;
	if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
		shift = 10.0 * app->info.delta_time * CONST_SPEED;
	handle_horizontal_translation(app, shift, i, last_changed);
	if (app->keyboard.state[SDL_SCANCODE_O])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			0, -0.1 * app->unit_size * shift, 0);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_L])
	{
		l3d_3d_object_translate(app->editor.selected_objects[i],
			0, 0.1 * app->unit_size * shift, 0);
		*last_changed = SDL_GetTicks();
	}
}

static void		handle_object_scaling_input(t_doom3d *app,
					int32_t i, uint32_t *last_changed)
{
	if (app->keyboard.state[SDL_SCANCODE_LEFTBRACKET])
	{
		l3d_3d_object_scale(app->editor.selected_objects[i],
			1.0 / 1.1, 1.0 / 1.1, 1.0 / 1.1);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_RIGHTBRACKET])
	{
		l3d_3d_object_scale(app->editor.selected_objects[i],
			1.1, 1.1, 1.1);
		*last_changed = SDL_GetTicks();
	}
}

/*
** Handle object transformation in editor
*/

void			handle_editor_transform_input(t_doom3d *app)
{
	static uint32_t		last_changed;
	uint32_t			prev_changed;
	uint32_t			diff;
	int32_t				i;

	diff = SDL_GetTicks() - last_changed;
	if (app->editor.is_saving || app->editor.num_selected_objects == 0)
		return ;
	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		prev_changed = last_changed;
		if (diff > 10)
			handle_object_translation_input(app, i, &last_changed);
		if (diff > 40)
			handle_object_scaling_input(app, i, &last_changed);
		if (prev_changed != last_changed)
			app->editor.is_saved = false;
	}
}
