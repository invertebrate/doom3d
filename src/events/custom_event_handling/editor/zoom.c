/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:12:10 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:12:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_zoom(t_doom3d *app, int32_t zoom_amount)
{
	t_vec3	dir;

	ml_vector3_mul(app->player.forward, zoom_amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}
