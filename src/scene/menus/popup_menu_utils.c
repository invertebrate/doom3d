/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popup_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:33:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 16:08:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void				active_scene_popup_menu_destroy(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		if (app->editor.editor_menu != NULL)
		{
			button_popup_menu_destroy(app->editor.editor_menu);
			app->editor.editor_menu_id = editor_menu_none;
			app->editor.editor_menu = NULL;
		}
	}
}

void				editor_popup_menu_set(t_doom3d *app, t_vec2 pos,
						t_button_menu_params params)
{
	uint32_t	bg_and_border_color[2];

	bg_and_border_color[0] = CLEAR_COLOR;
	bg_and_border_color[1] = 0xffffffff;
	app->editor.editor_menu = button_popup_menu_create(
			button_menu_create(app, params), pos, 3,
			bg_and_border_color);
}
