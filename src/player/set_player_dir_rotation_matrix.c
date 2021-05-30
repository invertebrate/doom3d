/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_by_player_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 18:28:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 01:23:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Rotates object so that it is oriented towards player
*/

void	set_player_dir_rotation_matrix(t_doom3d *app)
{
	t_mat4		rot_x;
	t_mat4		rot_y;

	ml_matrix4_rotation_y(ml_rad(app->player.rot_x), rot_x);
	ml_matrix4_rotation_x(ml_rad(app->player.rot_y), rot_y);
	ml_matrix4_mul(rot_x, rot_y, app->player.dir_rotation);
}
