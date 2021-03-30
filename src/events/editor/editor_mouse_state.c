/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:37:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:31:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				xyz_rotation(t_doom3d *app, int32_t i,
							int32_t x, uint32_t *last_rotated)
{
	float				angle;

	if (app->keyboard.state[SDL_SCANCODE_Y] && ft_abs(x) > 2)
	{
		angle = (x > 0 ? 1 : -1) * 10;
		l3d_3d_object_rotate(app->editor.selected_objects[i], 0, angle, 0);
		*last_rotated = SDL_GetTicks();
		if (app->editor.selected_objects[i]->type == object_type_npc)
			((t_npc*)app->editor.selected_objects[i]->params)->angle += angle;
	}
	else if (app->keyboard.state[SDL_SCANCODE_Z] &&
		ft_abs(x) > 2)
	{
		l3d_3d_object_rotate(app->editor.selected_objects[i],
			0, 0, (x > 0 ? 1 : -1) * 10);
		*last_rotated = SDL_GetTicks();
	}
	else if (app->keyboard.state[SDL_SCANCODE_X] && ft_abs(x) > 2)
	{
		l3d_3d_object_rotate(app->editor.selected_objects[i],
			(x > 0 ? 1 : -1) * 10, 0, 0);
		*last_rotated = SDL_GetTicks();
	}
}

static void				handle_object_rotation(t_doom3d *app, int32_t xrel)
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
			xyz_rotation(app, i, xrel, &last_rotated);
		if (prev_rotated != last_rotated)
		{
			app->editor.is_saved = false;
			after_editor_transform(app, &last_rotated);
			l3d_object_aabb_update(app->editor.selected_objects[i]);
		}
	}
}

void					handle_editor_obj_placement(t_doom3d *app)
{
	t_vec3		new_pos;
	t_3d_object	*place_object;

	place_object = app->editor.selected_objects[0];
	editor_pos_camera_front(app, new_pos);
	editor_point_on_target(app, new_pos);
	ml_vector3_sub(new_pos, place_object->position, new_pos);
	l3d_3d_object_translate(place_object,
		new_pos[0], new_pos[1], new_pos[2]);
}

void					handle_editor_mouse_state(t_doom3d *app)
{
	int32_t		xrel;
	int32_t		yrel;

	if ((app->mouse.state & SDL_BUTTON_MMASK))
	{
		app->editor.is_moving = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
		handle_player_rotation(app, xrel, yrel);
	}
	else
	{
		app->editor.is_moving = false;
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_GetRelativeMouseState(&xrel, &yrel);
		if (!app->keyboard.state[SDL_SCANCODE_R] &&
			app->editor.is_placing && app->editor.num_selected_objects > 0
			&& mouse_inside_editor_view(app))
			handle_editor_obj_placement(app);
		if (app->editor.num_selected_objects > 0 &&
			app->keyboard.state[SDL_SCANCODE_R])
			handle_object_rotation(app, xrel);
	}
}
