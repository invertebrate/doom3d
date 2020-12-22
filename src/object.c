/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:36:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 15:57:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Without textures & normal maps
*/

void		place_object_from_file(t_doom3d *app, char *filename, t_vec3 pos)
{
	app->active_scene->objects[app->active_scene->num_objects++] =
		l3d_read_obj(filename, NULL, NULL);
	l3d_3d_object_translate(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		pos[0], pos[1], pos[2]);
}

void		place_object(t_doom3d *app, t_3d_object *model, t_vec3 pos)
{
	app->active_scene->objects[app->active_scene->num_objects++] =
		l3d_object_instantiate(model, app->unit_size, false);
	l3d_3d_object_translate(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		pos[0], pos[1], pos[2]);
}

void		place_object_with_assets(t_doom3d *app, t_3d_object *model,
				t_vec3 pos)
{

}
