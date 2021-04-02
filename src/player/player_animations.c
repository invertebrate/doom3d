/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:35:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/02 18:09:28 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_surface	*get_1080p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/shotgun_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_glock)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/pistol_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/fist_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/rpg_anim_1080p.bmp"));
	return (NULL);
}

static t_surface	*get_720p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/shotgun_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_glock)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/pistol_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/fist_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/rpg_anim_720p.bmp"));
	return (NULL);
}

static t_surface	*get_540p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/shotgun_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_glock)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/pistol_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/fist_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/rpg_anim_540p.bmp"));
	return (NULL);
}

/*
** This function is called in `src/render/player_hud.c` in
** `player_animation_render` and it determines which source image is used
** for animation based on equipped weapon
*/

t_surface			*get_animation_source(t_doom3d *app)
{
	if (app->settings.height == 1080)
	{
		return (get_1080p_animation_source(app));
	}
	else if (app->settings.height == 720)
	{
		return (get_720p_animation_source(app));
	}
	else if (app->settings.height == 540)
	{
		return (get_540p_animation_source(app));
	}
	return (NULL);
}

static void			set_anim_frame_info(t_doom3d *app,
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
	anim->interruptable = true;
	anim->frame_time = 40;
}

static void			player_default_animations_init(t_doom3d *app)
{
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_default], 0, 1);
	set_anim_frame_info(app,
		&app->animations[anim_glock_default], 0, 1);
	set_anim_frame_info(app,
		&app->animations[anim_rpg_default], 0, 1);
	set_anim_frame_info(app,
		&app->animations[anim_rpg_special], 4, 1);
	set_anim_frame_info(app,
		&app->animations[anim_fist_default], 0, 1);
}

/*
** Initializes the frame information for each animation the player has
*/

void	player_animations_init(t_doom3d *app)
{
	player_default_animations_init(app);
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_glock_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_rpg_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_fist_shoot], 0, 5);
	set_anim_frame_info(app,
		&app->animations[anim_shotgun_reload], 5, 8);
	app->animations[anim_shotgun_reload].frame_time = 120;
	app->animations[anim_shotgun_reload].interruptable = false;
	set_anim_frame_info(app,
		&app->animations[anim_glock_reload], 5, 8);
	app->animations[anim_glock_reload].frame_time = 120;
	app->animations[anim_glock_reload].interruptable = false;
	set_anim_frame_info(app,
		&app->animations[anim_rpg_reload], 5, 8);
	app->animations[anim_rpg_reload].frame_time = 120;
	app->animations[anim_rpg_reload].interruptable = false;
	set_anim_frame_info(app,
		&app->animations[anim_fist_reload], 5, 8);
	app->animations[anim_fist_reload].frame_time = 120;
	app->animations[anim_fist_reload].interruptable = false;
}

/*
** If current animation is interruptable or finished, the new animation defined
** by animation_id becomes current animation.
*/

static void				set_player_animation(t_doom3d *app, uint32_t animation_id)
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

/*
** This function is called when player animation is to be switched to
** shoot animation
*/

void					set_player_shoot_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_shoot);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_shoot);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_shoot);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		set_player_animation(app, anim_rpg_shoot);
}

/*
** This function is called when player animation is to be switched to
** default animation
*/

void					set_player_default_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_default);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_default);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_default);
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		if (app->player.equipped_weapon->clip == 0)
			set_player_animation(app, anim_rpg_special);
		else
			set_player_animation(app, anim_rpg_default);
	}
}

/*
** This function is called when player animation is to be switched to
** reload animation
*/

void					set_player_reload_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_reload);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_reload);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_reload);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		set_player_animation(app, anim_rpg_reload);
}

/*
** Moves on animation frames if they should be moved on. If An animation frame
** is finished, the frames don't get incremented. Frame time left is decreased
** by delta time until it's <= 0. Current frame moves to next. Once last
** frame is reached, animation is set to be finished.
*/

void	doom3d_player_animation_update(t_doom3d *app)
{
	t_sprite_anim *curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (app->active_scene->scene_id != scene_id_main_game ||
		curr_player_anim->is_finished)
		return ;
	curr_player_anim->frame_time_left -= app->info.delta_time;
	if (curr_player_anim->frame_time_left <= 0)
	{
		curr_player_anim->frame_time_left = 0;
		curr_player_anim->current_frame++;
		curr_player_anim->frame_time_left =
			curr_player_anim->frame_time;
		if (curr_player_anim->current_frame >= curr_player_anim->num_frames)
		{
			curr_player_anim->is_finished = true;
			curr_player_anim->current_frame = 0;
		}
	}
}