/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_shading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:41:02 by veilo             #+#    #+#             */
/*   Updated: 2021/04/28 19:22:47 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_flip_lights(t_doom3d *app)
{
	if (app->editor.lights_enabled == false)
	{
		extend_all_objects_shading_opts(app, e_shading_lit);
		app->editor.lights_enabled = true;
	}
	else if (app->editor.lights_enabled == true)
	{
		remove_all_objects_shading_opts(app, e_shading_lit);
		app->editor.lights_enabled = false;
	}
}
