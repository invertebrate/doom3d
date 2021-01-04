/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:34:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/04 20:40:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void    editor_init(t_doom3d *app)
{
	ft_memset(&app->editor, 0, sizeof(t_editor));
	app->editor.editor_level = 0;
	ft_memset(app->editor.editor_filename, 0,
		sizeof(app->editor.editor_filename));
	ft_memset(app->editor.editor_savename, 0,
		sizeof(app->editor.editor_savename));
	ft_memset(app->editor.selected_object_str, 0,
		sizeof(app->editor.selected_object_str));
	ft_memcpy(app->editor.editor_filename, app->level_list[app->current_level],
		ft_strlen(app->level_list[app->current_level]));
	ft_memcpy(app->editor.editor_savename, app->editor.editor_filename,
		ft_strlen(app->editor.editor_filename));
}