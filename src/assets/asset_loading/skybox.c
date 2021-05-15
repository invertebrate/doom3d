/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:40:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:36:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	load_skybox_textures_to_memory(t_assets *assets)
{
	assets->skybox_textures[0] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/front.bmp");
	assets->skybox_textures[1] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/left.bmp");
	assets->skybox_textures[2] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/top.bmp");
	assets->skybox_textures[3] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/back.bmp");
	assets->skybox_textures[4] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/right.bmp");
	assets->skybox_textures[5] = l3d_read_bmp_32bit_rgba_surface(
			"assets/skybox/bottom.bmp");
}
