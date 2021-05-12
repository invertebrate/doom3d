/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_editor_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:00:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 11:03:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	editor_player_init(t_doom3d *app)
{
	t_3d_object		*start;
	t_vec3			pos;

	start = find_one_object_by_type(app, object_type_trigger,
			trigger_player_start);
	if (start)
	{
		ml_vector3_add(start->position, (t_vec3){0, 0, app->unit_size}, pos);
		player_init(app, pos);
	}
	else
	{
		player_init(app,
			(t_vec3){0, -10 * app->unit_size, -20 * app->unit_size});
		player_rotate_vertical(app, -90);
	}
}
