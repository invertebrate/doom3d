/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:37:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:37:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				xyz_rotation_input(t_doom3d *app, int32_t i,
							int32_t x, uint32_t *last_rotated)
{
	int32_t				angle;
	t_3d_object			*obj;
	void				*angle_pass;

	obj = app->editor.selected_objects[i];
	angle = (x > 0 ? 1 : -1) * 10;
	angle_pass = (void*)(intptr_t)angle;
	if (app->keyboard.state[SDL_SCANCODE_Y] && ft_abs(x) > 2)
	{
		push_custom_event(app, event_object_rotate_y, obj, angle_pass);
		*last_rotated = SDL_GetTicks();
		if (app->editor.selected_objects[i]->type == object_type_npc)
			((t_npc*)app->editor.selected_objects[i]->params)->angle += angle;
	}
	else if (app->keyboard.state[SDL_SCANCODE_Z] &&
		ft_abs(x) > 2)
	{
		push_custom_event(app, event_object_rotate_z, obj, angle_pass);
		*last_rotated = SDL_GetTicks();
	}
	else if (app->keyboard.state[SDL_SCANCODE_X] && ft_abs(x) > 2)
	{
		push_custom_event(app, event_object_rotate_x, obj, angle_pass);
		*last_rotated = SDL_GetTicks();
	}
}

static void				handle_object_rotation_input(t_doom3d *app,
							int32_t xrel)
{
	static uint32_t		last_rotated;
	uint32_t			prev_rotated;
	uint32_t			diff;
	int32_t				i;

	if (app->editor.num_selected_objects == 0)
		return ;
	diff = SDL_GetTicks() - last_rotated;
	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		prev_rotated = last_rotated;
		if (diff > 50)
			xyz_rotation_input(app, i, xrel, &last_rotated);
		if (prev_rotated != last_rotated)
			app->editor.is_saved = false;
	}
}

static void				handle_editor_player_rotation_input(t_doom3d *app,
							int32_t *xrel, int32_t *yrel)
{
	app->editor.is_rotating = true;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(xrel, yrel);
	push_custom_event(app, event_editor_rotate_view,
		(void*)(intptr_t)*xrel, (void*)(intptr_t)*yrel);
}

void					handle_editor_mouse_state_input(t_doom3d *app)
{
	int32_t		xrel;
	int32_t		yrel;

	if ((app->mouse.state & SDL_BUTTON_MMASK) ||
		(app->keyboard.state[SDL_SCANCODE_LALT]))
		handle_editor_player_rotation_input(app, &xrel, &yrel);
	else
	{
		app->editor.is_rotating = false;
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
		if (!app->keyboard.state[SDL_SCANCODE_R] &&
			app->editor.is_placing && app->editor.num_selected_objects > 0
			&& mouse_inside_editor_view(app))
			push_custom_event(app, event_editor_in_placement_move, NULL, NULL);
		if (app->editor.num_selected_objects > 0 &&
			app->keyboard.state[SDL_SCANCODE_R])
			handle_object_rotation_input(app, xrel);
	}
}
