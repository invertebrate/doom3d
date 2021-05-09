/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_too_far.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:33:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/07 21:12:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool	object_too_far(t_doom3d *app, t_3d_object *obj)
{
	float		too_far;
	t_vec3		player_to_obj_min;
	t_vec3		player_to_obj_max;

	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * GAME_VIEW_DIST_UNITS;
	else
		too_far = app->unit_size * EDITOR_VIEW_DIST_UNITS;
	ml_vector3_sub(obj->aabb.xyz_min, app->player.pos,
		player_to_obj_min);
	ml_vector3_sub(obj->aabb.xyz_max, app->player.pos,
		player_to_obj_max);
	if (ml_vector3_mag(player_to_obj_min) > too_far
		&& ml_vector3_mag(player_to_obj_max) > too_far &&
		!l3d_point_inside_aabb(&obj->aabb, app->player.pos))
		return (true);
	
	return (false);
}
