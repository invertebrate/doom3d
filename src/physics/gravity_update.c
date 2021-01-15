/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/15 18:54:03 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	player_fall(t_doom3d *app, float velocity)
{
	t_vec3		add;
	t_vec3		down;

	ml_vector3_copy((t_vec3){0, -Y_DIR, 0}, down);
	ml_vector3_mul(down, velocity, add);
	ml_vector3_add(app->player.pos, add, app->player.pos);
	ml_matrix4_translation(app->player.pos[0],
		app->player.pos[1], app->player.pos[2], app->player.translation);
	ml_matrix4_inverse(app->player.translation, app->player.inv_translation);
	player_update_aabb(&app->player);
}


void		gravity_update(t_doom3d *app, t_3d_object *target)
{
	t_npc	*npc;

	npc = target->params;
	if (obj_is_grounded(app, target))
		npc->y_velocity = 0;
	else
	{
		npc->y_velocity += app->info.delta_time / 10;
		l3d_3d_object_translate(target, 0, npc->y_velocity, 0);
	}
	player_fall(app, app->player.y_velocity);
	if (app->player.flying == true || player_is_grounded(app))
		app->player.y_velocity = 0;
	else
		app->player.y_velocity += app->info.delta_time / 10;
}
