/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:52:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 11:54:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

uint32_t		get_light_emit_color(t_3d_object *light_obj)
{
	t_light_type	light_type;

	if (light_obj->type == object_type_light)
	{
		light_type = light_obj->params_type;
		if (light_type == light_type_yellow)
			return (L3D_COLOR_YELLOW);
		else if (light_type == light_type_red)
			return (L3D_COLOR_RED);
		else if (light_type == light_type_green)
			return (L3D_COLOR_GREEN);
		else if (light_type == light_type_blue)
			return (L3D_COLOR_BLUE);
		else if (light_type == light_type_cyan)
			return (L3D_COLOR_CYAN);
		else if (light_type == light_type_explosion)
			return (L3D_COLOR_EXPLOSION);
		return (L3D_COLOR_YELLOW);
	}
	else
		return (L3D_COLOR_EXPLOSION);
}

t_shading_opts	get_light_shading(t_light_type light_type)
{
	if (light_type == light_type_yellow)
		return (e_shading_yellow);
	else if (light_type == light_type_red)
		return (e_shading_red);
	else if (light_type == light_type_green)
		return (e_shading_green);
	else if (light_type == light_type_blue)
		return (e_shading_blue);
	else if (light_type == light_type_cyan)
		return (e_shading_cyan);
	return (e_shading_yellow);
}
