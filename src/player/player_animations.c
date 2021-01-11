/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:35:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/11 23:12:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_surface			*get_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return (hash_map_get(app->active_scene->textures,
			(int64_t)"assets/textures/shotgun_animation.bmp"));
	return (NULL);
}

static void			set_shotgun_default_anim(t_sprite_anim *anim)
{
	anim->frames[0].width = 480;
	anim->frames[0].height = 528;
	anim->frames[0].x_offset = 0;
	anim->frames[0].y_offset = 0;
	anim->num_frames = 1;
	anim->id = anim_shotgun_shoot;
	anim->interruptable = true;
}

static void			set_shotgun_reload_anim(t_sprite_anim *anim)
{
	anim->current_frame = 0;
	anim->frames[0].width = 480;
	anim->frames[1].width = 480;
	anim->frames[2].width = 480;
	anim->frames[0].height = 528;
	anim->frames[1].height = 528;
	anim->frames[2].height = 528;
	anim->frames[0].x_offset = 480 * 4;
	anim->frames[1].x_offset = 480 * 5;
	anim->frames[2].x_offset = 480 * 6;
	anim->frames[0].y_offset = 0;
	anim->frames[1].y_offset = 0;
	anim->frames[2].y_offset = 0;
	anim->num_frames = 3;
	anim->id = anim_shotgun_reload;
	anim->interruptable = false;
}

static void			set_shotgun_shoot_anim(t_sprite_anim *anim)
{
	anim->current_frame = 0;
	anim->frames[0].width = 480;
	anim->frames[1].width = 480;
	anim->frames[2].width = 480;
	anim->frames[3].width = 480;
	anim->frames[0].height = 528;
	anim->frames[1].height = 528;
	anim->frames[2].height = 528;
	anim->frames[3].height = 528;
	anim->frames[0].x_offset = 0;
	anim->frames[1].x_offset = 480 * 1;
	anim->frames[2].x_offset = 480 * 2;
	anim->frames[3].x_offset = 480 * 3;
	anim->frames[0].y_offset = 0;
	anim->frames[1].y_offset = 0;
	anim->frames[2].y_offset = 0;
	anim->frames[3].y_offset = 0;
	anim->num_frames = 4;
	anim->id = anim_shotgun_shoot;
	anim->interruptable = false;
}

void	init_player_animations(t_doom3d *app)
{
	set_shotgun_default_anim(&app->animations[anim_shotgun_default]);
	set_shotgun_reload_anim(&app->animations[anim_shotgun_reload]);
	set_shotgun_shoot_anim(&app->animations[anim_shotgun_shoot]);
}

static void				set_player_animation(t_doom3d *app, uint32_t animation_id)
{
	t_sprite_anim *curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (!(curr_player_anim->is_finished || curr_player_anim->interruptable))
		return ;
	app->animations[app->player_hud.curr_animation].current_frame = 0;
	app->animations[app->player_hud.curr_animation].frame_time =
		ANIM_FRAME_TIME_MS;
	app->animations[app->player_hud.curr_animation].is_finished = false;
	app->player_hud.curr_animation = animation_id;
}

void					set_player_shoot_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->item_type == item_type_weapon)
	{
		if (app->player.equipped_weapon->id == weapon_shotgun)
			set_player_animation(app, anim_shotgun_shoot);
	}
}

void					set_player_default_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->item_type == item_type_weapon)
	{
		if (app->player.equipped_weapon->id == weapon_shotgun)
			set_player_animation(app, anim_shotgun_default);
		else
			set_player_animation(app, anim_none);
	}
}

void					set_player_reload_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->item_type == item_type_weapon)
	{
		if (app->player.equipped_weapon->id == weapon_shotgun)
			set_player_animation(app, anim_shotgun_reload);
	}
}

void	doom3d_player_animation_update(t_doom3d *app)
{
	t_sprite_anim *curr_player_anim;

	if (app->active_scene->scene_id != scene_id_main_game)
		return ;
	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	curr_player_anim->frame_time -= app->info.delta_time;
	if (curr_player_anim->frame_time <= 0)
	{
		curr_player_anim->frame_time = 0;
		curr_player_anim->current_frame++;
		curr_player_anim->frame_time = ANIM_FRAME_TIME_MS;
		if (curr_player_anim->current_frame >= curr_player_anim->num_frames)
		{
			curr_player_anim->is_finished = true;
			curr_player_anim->current_frame = 0;
		}
	}
}