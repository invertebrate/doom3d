/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 01:57:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:02:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_in_placement_move(t_doom3d *app)
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
