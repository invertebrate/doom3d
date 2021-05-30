/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 21:18:25 by veilo             #+#    #+#             */
/*   Updated: 2021/05/30 21:33:06 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	editor_handle_prefab_place(t_doom3d *app, void *data,
	t_3d_object **object)
{

	if ((t_prefab_type)data == prefab_plane)
		*object = place_plane_prefab(app);
	else if ((t_prefab_type)data == prefab_window_wall)
		*object = place_window_wall_prefab(app);
	else if ((t_prefab_type)data == prefab_reactor)
		*object = place_reactor_prefab(app);
	else if ((t_prefab_type)data == prefab_hologram)
		*object = place_hologram_prefab(app);
	else if ((t_prefab_type)data == prefab_lava_plane)
		*object = place_lava_plane_prefab(app);
	else if ((t_prefab_type)data == prefab_path_node)
	{
		*object = place_path_object(app);
		placement_notification(app, "Placing Path Node!");
	}
}
