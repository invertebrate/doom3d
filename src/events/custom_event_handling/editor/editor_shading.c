/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_shading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:41:02 by veilo             #+#    #+#             */
/*   Updated: 2021/04/30 17:58:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_flip_lights(t_doom3d *app)
{
	app->editor.lights_enabled = !app->editor.lights_enabled;
	if (app->editor.lights_enabled == false)
		extend_all_objects_shading_opts(app, e_shading_lit);
	else
		remove_all_objects_shading_opts(app, e_shading_lit);
}
