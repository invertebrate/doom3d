/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:12:10 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 17:08:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_zoom(t_doom3d *app, int32_t zoom_amount)
{
	t_vec3	dir;

	ml_vector3_mul(app->player.forward, zoom_amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}

void		handle_editor_move_view_forward(t_doom3d *app,
				int32_t amount)
{
	t_vec3	dir;

	if (app->editor.is_locked_vertical_movement)
	{
		get_move_dir(app, move_forward, dir);
		ml_vector3_mul(dir, amount, dir);
	}
	else
		ml_vector3_mul(app->player.forward, amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}

void		handle_editor_move_view_sideways(t_doom3d *app,
				int32_t amount)
{
	t_vec3	dir;

	ml_vector3_mul(app->player.sideways, amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}

void		handle_editor_rotate_view(t_doom3d *app, int32_t xrel, int32_t yrel)
{
	player_rotate_vertical(app, -(float)yrel * 0.3);
	player_rotate_horizontal(app, (float)xrel * 0.3);
}

void		handle_editor_toggle_vertical_lock(t_doom3d *app)
{
	app->editor.is_locked_vertical_movement =
		!app->editor.is_locked_vertical_movement;
	if (app->editor.is_locked_vertical_movement)
		notify_user(app, (t_notification){
			.message = "Toggled vertical movement on!",
			.type = notification_type_info, .time = 2000});
	else
		notify_user(app, (t_notification){
			.message = "Toggled vertical movement off!",
			.type = notification_type_info, .time = 2000});
}
