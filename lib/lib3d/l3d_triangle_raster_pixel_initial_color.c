/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster_pixel_initial_color.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:47:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 19:53:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

uint32_t	get_pixel_initial_color_trans(t_triangle *triangle)
{
	uint32_t		pixel;
	t_shading_opts	shading;

	shading = triangle->material->shading_opts;
	if (shading & e_shading_green)
		pixel = L3D_COLOR_GREEN_TRANSPARENT;
	else if (shading & e_shading_red)
		pixel = L3D_COLOR_RED_TRANSPARENT;
	else if (shading & e_shading_yellow)
		pixel = L3D_COLOR_YELLOW_TRANSPARENT;
	else if (shading & e_shading_cyan)
		pixel = L3D_COLOR_CYAN_TRANSPARENT;
	else if ((shading & e_shading_blue) || (shading & e_shading_blue_highlight))
		pixel = L3D_COLOR_BLUE_TRANSPARENT;
	else
		pixel = L3D_DEFAULT_COLOR_TRANSPARENT;
	return (pixel);
}

uint32_t	get_pixel_initial_color(t_triangle *triangle)
{
	uint32_t		pixel;
	t_shading_opts	shading;

	shading = triangle->material->shading_opts;
	if (shading & e_shading_green)
		pixel = L3D_COLOR_GREEN;
	else if (shading & e_shading_red)
		pixel = L3D_COLOR_RED;
	else if (shading & e_shading_yellow)
		pixel = L3D_COLOR_YELLOW;
	else if ((shading & e_shading_blue) || (shading & e_shading_blue_highlight))
		pixel = L3D_COLOR_BLUE;
	else if (shading & e_shading_cyan)
		pixel = L3D_COLOR_CYAN;
	else
		pixel = L3D_DEFAULT_COLOR;
	return (pixel);
}
