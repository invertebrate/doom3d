/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 00:43:13 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 19:02:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	object_custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_object_delete)
		ft_sprintf(str, "event_object_delete");
	else if (code == event_object_scale)
		ft_sprintf(str, "event_object_scale");
	else if (code == event_object_translate_x)
		ft_sprintf(str, "event_object_translate_x");
	else if (code == event_object_translate_y)
		ft_sprintf(str, "event_object_translate_y");
	else if (code == event_object_translate_z)
		ft_sprintf(str, "event_object_translate_z");
	else if (code == event_object_rotate_x)
		ft_sprintf(str, "event_object_rotate_x");
	else if (code == event_object_rotate_y)
		ft_sprintf(str, "event_object_rotate_y");
	else if (code == event_object_rotate_z)
		ft_sprintf(str, "event_object_rotate_z");
	else if (code == event_object_scale_with_uvs)
		ft_sprintf(str, "event_object_scale_with_uvs");
	else if (code == event_object_set_shading_not_cull)
		ft_sprintf(str, "event_object_set_shading_not_cull");
}

void	register_object_custom_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_object_scale,
		(void *)handle_object_scale);
	hash_map_add(app->custom_event_handles, event_object_scale_with_uvs,
		(void *)handle_object_scale_with_uvs);
	hash_map_add(app->custom_event_handles, event_object_translate_x,
		(void *)handle_object_translate_x);
	hash_map_add(app->custom_event_handles, event_object_translate_y,
		(void *)handle_object_translate_y);
	hash_map_add(app->custom_event_handles, event_object_translate_z,
		(void *)handle_object_translate_z);
	hash_map_add(app->custom_event_handles, event_object_rotate_x,
		(void *)handle_object_rotate_x);
	hash_map_add(app->custom_event_handles, event_object_rotate_y,
		(void *)handle_object_rotate_y);
	hash_map_add(app->custom_event_handles, event_object_rotate_z,
		(void *)handle_object_rotate_z);
	hash_map_add(app->custom_event_handles, event_object_delete,
		(void *)handle_object_deletion);
	hash_map_add(app->custom_event_handles, event_object_set_shading_not_cull,
		(void *)handle_object_set_shading_not_cull);
}
