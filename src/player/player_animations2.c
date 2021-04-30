/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:25:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/30 21:27:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				set_anim_frame_info(t_doom3d *app,
							t_sprite_anim *anim, int32_t index_offset,
							int32_t num_frames)
{
	int32_t		i;

	anim->num_frames = num_frames;
	i = index_offset - 1;
	while (++i < anim->num_frames)
	{
		anim->frames[i - index_offset].width = app->settings.width;
		anim->frames[i - index_offset].height = app->settings.height;
		anim->frames[i - index_offset].x_offset = i * app->settings.width;
		anim->frames[i - index_offset].y_offset = 0;
	}
	anim->interruptable = false;
	anim->frame_time = 40;
}

static void				player_default_animations_init(t_doom3d *app)
{
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_default], 0, 1);
	app->animations[anim_shotgun_default].interruptable = true;
	set_anim_frame_info(app,
		&app->animations[anim_pistol_default], 0, 1);
	app->animations[anim_pistol_default].interruptable = true;
	set_anim_frame_info(app,
		&app->animations[anim_rpg_default], 0, 1);
	app->animations[anim_rpg_default].interruptable = true;
	set_anim_frame_info(app,
		&app->animations[anim_rpg_special], 4, 1);
	app->animations[anim_rpg_special].interruptable = true;
	set_anim_frame_info(app,
		&app->animations[anim_fist_default], 0, 1);
	app->animations[anim_fist_default].interruptable = true;
}

/*
** Initializes the frame information for each animation the player has
*/

void					player_animations_init(t_doom3d *app)
{
	player_default_animations_init(app);
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_pistol_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_rpg_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_fist_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_reload], 5, 8);
	app->animations[anim_shotgun_reload].frame_time = 120;
	set_anim_frame_info(app,
		&app->animations[anim_pistol_reload], 5, 8);
	app->animations[anim_pistol_reload].frame_time = 120;
	set_anim_frame_info(app,
		&app->animations[anim_rpg_reload], 5, 8);
	app->animations[anim_rpg_reload].frame_time = 120;
	set_anim_frame_info(app,
		&app->animations[anim_fist_reload], 5, 8);
	app->animations[anim_fist_reload].frame_time = 120;
}

/*
** If current animation is interruptable or finished, the new animation defined
** by animation_id becomes current animation.
*/

void					set_player_animation(t_doom3d *app,
											uint32_t animation_id)
{
	t_sprite_anim *curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (app->player.is_reloading && curr_player_anim->is_finished)
	{
		app->player.is_reloading = false;
		player_reload_finish(app);
	}
	if (!(curr_player_anim->is_finished || curr_player_anim->interruptable))
		return ;
	app->animations[app->player_hud.curr_animation].current_frame = 0;
	app->animations[app->player_hud.curr_animation].frame_time_left =
		app->animations[app->player_hud.curr_animation].frame_time;
	app->animations[app->player_hud.curr_animation].is_finished = false;
	app->player_hud.curr_animation = animation_id;
}
