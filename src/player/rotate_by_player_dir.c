/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_by_player_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 18:28:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 23:04:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Rotates object so that it is oriented towards player
*/

void	rotate_object_by_player_dir(t_doom3d *app, t_3d_object *obj)
{
	t_mat4		rot_x;
	t_mat4		rot_y;
	t_mat4		rot;

	ml_matrix4_rotation_y(ml_rad(app->player.rot_x), rot_x);
	ml_matrix4_rotation_x(ml_rad(app->player.rot_y), rot_y);
	ml_matrix4_mul(rot_x, rot_y, rot);
	l3d_3d_object_rotate_matrix(obj, rot);
}
