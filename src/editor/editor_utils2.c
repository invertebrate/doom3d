/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:13:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 17:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Set non-distance-culled objects to be highlighted in editor
*/

void	editor_objects_non_culled_highlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (obj == NULL)
			continue ;
		if (obj->material->shading_opts & e_shading_dont_cull)
			obj->material->shading_opts |= e_shading_blue_highlight;
	}
}

/*
** Set non-distance-culled objects to be invisible again
*/

void	editor_objects_non_culled_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (obj == NULL)
			continue ;
		if (obj->material->shading_opts & e_shading_dont_cull)
		{
			obj->material->shading_opts = (obj->material->shading_opts
					& ~(e_shading_blue_highlight));
		}
	}
}
