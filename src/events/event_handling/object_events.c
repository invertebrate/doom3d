/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:32:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 16:08:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			handle_object_deletion(t_doom3d *app, t_3d_object *object)
{
	int32_t		i;
	uint32_t	del_index;
	int32_t		sum;

	i = -1;
	sum = (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted);
	while (++i < sum)
	{
		if (app->active_scene->objects[i] != NULL &&
			app->active_scene->objects[i]->id == object->id)
		{
			app->active_scene->num_deleted++;
			app->active_scene->num_objects--;
			del_index = app->active_scene->num_deleted - 1;
			app->active_scene->deleted_object_i[del_index] = i;
			break ;
		}
	}
}
