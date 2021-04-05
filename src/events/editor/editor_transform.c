/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:12:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 01:53:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		handle_horizontal_translation(t_doom3d *app, int32_t amount,
					int32_t i, uint32_t *last_changed)
{
	t_3d_object	*obj;

	obj = app->editor.selected_objects[i];
	if (app->keyboard.state[SDL_SCANCODE_UP])
		push_custom_event(app, event_object_translate_z, obj,
			(void *)(intptr_t)amount);
	if (app->keyboard.state[SDL_SCANCODE_RIGHT])
		push_custom_event(app, event_object_translate_x, obj,
			(void *)(intptr_t)amount);
	if (app->keyboard.state[SDL_SCANCODE_DOWN])
		push_custom_event(app, event_object_translate_z, obj,
			(void *)(intptr_t)-amount);
	if (app->keyboard.state[SDL_SCANCODE_LEFT])
		push_custom_event(app, event_object_translate_x, obj,
			(void *)(intptr_t)-amount);
	if (app->keyboard.state[SDL_SCANCODE_LEFT] ||
		app->keyboard.state[SDL_SCANCODE_DOWN] ||
		app->keyboard.state[SDL_SCANCODE_RIGHT] ||
		app->keyboard.state[SDL_SCANCODE_UP])
		*last_changed = SDL_GetTicks();
}

static void		handle_object_translation_input(t_doom3d *app,
					int32_t i, uint32_t *last_changed)
{
	float				shift;
	int32_t				amount;

	shift = 1.0 * app->info.delta_time * CONST_SPEED;
	if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
		shift = 10.0 * app->info.delta_time * CONST_SPEED;
	amount = 0.1 * app->unit_size * shift;
	handle_horizontal_translation(app, amount, i, last_changed);
	if (app->keyboard.state[SDL_SCANCODE_O])
	{
		push_custom_event(app, event_object_translate_y,
			app->editor.selected_objects[i], (void *)(intptr_t)-amount);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_L])
	{
		push_custom_event(app, event_object_translate_y,
			app->editor.selected_objects[i], (void *)(intptr_t)amount);
		*last_changed = SDL_GetTicks();
	}
}

static void		handle_object_scaling_input(t_doom3d *app,
					int32_t i, uint32_t *last_changed)
{
	if (app->keyboard.state[SDL_SCANCODE_LEFTBRACKET])
	{
		push_custom_event(app, event_object_scale,
			app->editor.selected_objects[i], (void *)(intptr_t)1);
		*last_changed = SDL_GetTicks();
	}
	if (app->keyboard.state[SDL_SCANCODE_RIGHTBRACKET])
	{
		push_custom_event(app, event_object_scale,
			app->editor.selected_objects[i], (void *)(intptr_t)-1);
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
