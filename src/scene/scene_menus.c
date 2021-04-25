/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_menus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:47:22 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 18:47:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Recreate menus for scene
*/

void		active_scene_menus_create(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
		pause_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_editor3d)
		editor3d_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_main_menu)
		main_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_main_menu_settings)
		settings_menu_create(app);
}
