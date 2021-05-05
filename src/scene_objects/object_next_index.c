/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_next_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 22:50:47 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:09:55 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** // !Note that this (inc/dec)rements both num_deleted and num_objects
** so only use this when intending to actually place objects
** Saves this next index to last_object_index under scene
*/

uint32_t	next_object_index(t_doom3d *app)
{
	uint32_t	next_index;

	if (app->active_scene->num_deleted > 0)
	{
		next_index = app->active_scene->deleted_object_i[
			app->active_scene->num_deleted - 1];
		app->active_scene->num_deleted--;
	}
	else
		next_index = app->active_scene->num_objects;
	app->active_scene->num_objects++;
	app->active_scene->last_object_index = next_index;
	return (next_index);
}
