/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:34:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/27 02:15:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initialize editor (to null and falses mostly)
*/

void	editor_init(t_doom3d *app, int32_t editor_level)
{
	ft_memset(&app->editor, 0, sizeof(t_editor));
	app->editor.editor_level = editor_level;
	ft_memset(app->editor.editor_filename, 0,
		sizeof(app->editor.editor_filename));
	ft_memset(app->editor.editor_savename, 0,
		sizeof(app->editor.editor_savename));
	ft_memset(app->editor.selected_object_str, 0,
		sizeof(app->editor.selected_object_str));
	if (app->level_list[app->editor.editor_level])
	{
		ft_memcpy(app->editor.editor_filename,
			app->level_list[app->editor.editor_level],
			ft_strlen(app->level_list[app->editor.editor_level]));
		ft_memcpy(app->editor.editor_savename, app->editor.editor_filename,
			ft_strlen(app->editor.editor_filename));
	}
	app->editor.lights_enabled = true;
}
