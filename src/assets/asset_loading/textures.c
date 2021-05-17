/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:19:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 23:43:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	texture_files_set_sub1(t_asset_files *data)
{
	data->texture_files[data->num_textures++]
		= "assets/textures/door_metal_h.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/door_metal_v.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/wall_metal_panel.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/shotgun_texture.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/pistol_texture.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/rpg_texture.bmp";
}

static void	texture_files_set_sub2(t_asset_files *data)
{
	data->texture_files[data->num_textures++] = MONSTER01_TEXTURE;
	data->texture_files[data->num_textures++] = MONSTER01A_TEXTURE;
	data->texture_files[data->num_textures++] = MONSTER01B_TEXTURE;
	data->texture_files[data->num_textures++]
		= "assets/textures/monster_02/monster02_diffuse.bmp";
	data->texture_files[data->num_textures++]
		= NPC_PROJECTILE_00;
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_corner_floor.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_corner_inner.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_corner_outer.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_straight_floor.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_straight_wall.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_t_floor.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/corridor_x_floor.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/keypad_texture.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/medkit_texture.bmp";
}

static void	texture_files_set_sub3(t_asset_files *data)
{
	data->texture_files[data->num_textures++]
		= "assets/textures/rock_toxic.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/alien_floor.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/lava_molten.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/monster01_finalboss.bmp";
	data->texture_files[data->num_textures++]
		= NPC_PROJECTILE_01;
	data->texture_files[data->num_textures++]
		= NPC_PROJECTILE_02;
	data->texture_files[data->num_textures++]
		= "assets/textures/monitor_binary.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/monitor_pepe.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/lamp_breakable.bmp";
}

void	texture_files_set(t_asset_files *data)
{
	data->texture_files[data->num_textures++]
		= "assets/textures/lava.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/rock.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/crate.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/floor_dirt.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/floor_metal_2048.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/floor_metal3.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/floor_metal4.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/floor_metal4_box.bmp";
	data->texture_files[data->num_textures++]
		= "assets/textures/window_wall.bmp";
	texture_files_set_sub1(data);
	texture_files_set_sub2(data);
	texture_files_set_sub3(data);
}
