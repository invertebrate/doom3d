/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_editor3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:17:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 00:18:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void				editor3d_menu_render(t_doom3d *app, t_vec2 pos)
{
	if (pos[0] != app->editor_menu_3d->pos[0] ||
		pos[1] != app->editor_menu_3d->pos[1])
	{
		button_group_update_position(app->editor_menu_3d, pos);
	}
	button_group_render(app->editor_menu_3d);
}
