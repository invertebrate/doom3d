/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popup_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:33:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 03:33:18 by ohakola          ###   ########.fr       */
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
