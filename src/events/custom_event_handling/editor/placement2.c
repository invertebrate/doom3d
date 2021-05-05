/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 01:57:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:19:38 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_in_placement_move(t_doom3d *app)
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
