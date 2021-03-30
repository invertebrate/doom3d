/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:11:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 01:13:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Selects object by mouse when select object event is called
*/

void	handle_editor_select(t_doom3d *app)
{
	if (mouse_inside_editor_view(app))
		editor_select_by_mouse(app);
	if (app->editor.num_selected_objects == 0)
		app->active_scene->menus[1]->is_active = false;
	else
		app->active_scene->menus[1]->is_active = true;
}

/*
** Deselects object when select object event is called
*/

void	handle_editor_deselect(t_doom3d *app)
{
	editor_deselect(app);
	if (app->editor.num_selected_objects == 0)
		app->active_scene->menus[1]->is_active = false;	
}

