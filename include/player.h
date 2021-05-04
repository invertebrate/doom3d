/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:55:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 19:33:41 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define NUM_WEAPONS 4
# define NUM_PLAYER_ANIMATIONS 16
# define PLAYER_SPEED 8.0
# define PLAYER_MAX_SPEED 14.00
# define PLAYER_ROTATION_SPEED 0.1
# define ANIMATION_SCALE 2
# define PLAYER_JUMP_FORCE 8.0
# define PLAYER_HEIGHT 1.75
# define PLAYER_HEIGHT_CROUCH 0.75
# define MAX_KEYS 32
# define COLLIDER_RAY_COUNT 10
# define COLLIDER_RAY_TOTAL 10 * 10
# define PLAYER_COLLIDER_RADIUS 1
# define SLOPE_ANGLE_THRESHOLD 30

# include "lib3d.h"
# include "game_objects.h"

/*
** Directions to which player can move
*/

typedef enum				e_move
{
	move_forward,
	move_backward,
	move_strafe_left,
	move_strafe_right,
	move_upwards,
	move_downwards,
}							t_move;

/*
** A spherical collider that contains rays in every direction
*/

typedef struct s_sphere_collider
{
	t_ray			rays[COLLIDER_RAY_COUNT * COLLIDER_RAY_COUNT];
	t_sphere		sphere;
}							t_sphere_collider;


/*
** Data defining player functionality and toggles.
*/

typedef struct				s_player
{
	t_vec3					pos;
	t_vec3					forward;
	t_vec3					sideways;
	t_vec3					up;
	t_bool					is_running;
	t_bool					is_crouching;
	t_bool					is_shooting;
	t_bool					is_reloading;
	t_bool					is_moving;
	t_bool					is_rotating;
	t_physics_state			physics_state;
	t_bool					can_fly;
	float					jump_force;
	float					speed;
	float					rot_speed;
	float					rot_x;
	float					rot_y;
	float					player_height;
	float					fire_rate_per_sec;
	t_mat4					rotation;
	t_mat4					inv_rotation;
	t_mat4					translation;
	t_mat4					inv_translation;
	t_box3d					aabb;
	t_weapon				weapons[NUM_WEAPONS];
	t_weapon				*equipped_weapon;
	t_bool					keys[MAX_KEYS];
	int						hp;
	int						max_hp;
	t_vec3					velocity;
	t_flashlight			flashlight;
	t_sphere_collider		collider;
}							t_player;

/*
** A list of animations that the sprite animation under player hud
** will be able to display. Also defines the index of animation frame data
** in app->animations
*/

typedef enum				e_player_animation
{
	anim_none = 0,
	anim_shotgun_default = 1,
	anim_shotgun_shoot = 2,
	anim_shotgun_reload = 3,
	anim_pistol_default = 4,
	anim_pistol_shoot = 5,
	anim_pistol_reload = 6,
	anim_rpg_default = 7,
	anim_rpg_shoot = 8,
	anim_rpg_reload = 9,
	anim_rpg_special = 10,
	anim_fist_default = 12,
	anim_fist_shoot = 13,
	anim_fist_reload = 14,
}							t_player_animation;

/*
** Animation general state
*/

typedef enum				e_player_anim_state
{
	anim_state_default = 1,
	anim_state_shoot = 2,
	anim_state_reload = 3,
}							t_player_anim_state;

/*
** Data which defines different things that belong to player hud.
*/

typedef struct				s_player_hud
{
	t_player_animation		curr_animation;
}							t_player_hud;

#endif
