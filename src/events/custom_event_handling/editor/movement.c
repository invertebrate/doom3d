/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:12:10 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:35:11 by ohakola          ###   ########.fr       */
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
	handle_player_rotation_input(app, xrel, yrel);
}
