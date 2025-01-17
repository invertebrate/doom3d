/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_is_ignored.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:33:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 18:09:07 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool	object_is_ignored(t_doom3d *app, t_3d_object *obj)
{
	float		too_far;
	t_vec3		player_to_obj_min;
	t_vec3		player_to_obj_max;
	t_vec3		player_to_pos;

	if ((obj->type == object_type_light
			&& obj->params_type != light_type_breakable
			&& obj->params_type != light_type_mushroom)
		|| (obj->material->shading_opts & e_shading_dont_cull))
		return (false);
	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * GAME_VIEW_DIST_UNITS;
	else
		too_far = app->unit_size * EDITOR_VIEW_DIST_UNITS;
	ml_vector3_sub(obj->aabb.xyz_min, app->player.pos,
		player_to_obj_min);
	ml_vector3_sub(obj->aabb.xyz_max, app->player.pos,
		player_to_obj_max);
	ml_vector3_sub(obj->aabb.center, app->player.pos,
		player_to_pos);
	if (ml_vector3_mag(player_to_obj_min) > too_far
		&& ml_vector3_mag(player_to_obj_max) > too_far
		&& ml_vector3_mag(player_to_pos) > ml_vector3_mag(obj->aabb.size))
		return (true);
	return (false);
}
