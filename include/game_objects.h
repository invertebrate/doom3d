/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:36:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 15:50:40 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_OBJECTS_H
# define GAME_OBJECTS_H

# define MONSTER01_MODEL "assets/models/monster_01/monster01_basemodel_000.obj"
# define MONSTER01_TEXTURE "assets/textures/monster_01/monster01_diffuse.bmp"
# define MONSTER01A_TEXTURE "assets/textures/monster_01/monster01a_diffuse.bmp"
# define MONSTER01B_TEXTURE "assets/textures/monster_01/monster01b_diffuse.bmp"
# define MONSTER01_NORMM "assets/textures/monster_01/monster01_normal.bmp"

# define MONSTER02_MODEL "assets/models/monster_02/monster02_basemodel_000.obj"
# define MONSTER02_TEXTURE "assets/textures/monster_02/monster02_diffuse.bmp"
# define MONSTER02_NORMM "assets/textures/monster_02/monster02_normal.bmp"

# define NPC_ELEVATOR_MODEL "assets/models/box.obj"
# define NPC_ELEVATOR_TEXTURE "assets/textures/rock.bmp"
# define NPC_ELEVATOR_NORMM "assets/textures/rock.bmp"

# define ELEVATOR_SWITCH_TEXTURE "assets/textures/lava.bmp"

# include "libgmatrix.h"
# include "animations_3d.h"

# define PATH_NEIGHBOUR_MAX 8
# define MAX_PATROL_NODES 19
# define MAX_TRIGGER_LINKS 16
# define MAX_PATH_NODE_NETWORK_SIZE 256
# define MAX_ATTACK_PATTERN_SIZE 128

/*
** Projectile definitions
*/

# define NUM_PROJECTILES 10
# define NPC_PROJECTILE_00 "assets/textures/npc_projectile_texture.bmp"
# define NPC_PROJECTILE_01 "assets/textures/npc_projectile_texture_blue.bmp"
# define NPC_PROJECTILE_02 "assets/textures/npc_projectile_texture_green.bmp"
# define NPC_PROJECTILE_03 "assets/textures/npc_projectile_texture_l_green.bmp"
# define NPC_PROJECTILE_04 "assets/textures/npc_projectile_texture_pink.bmp"
# define NPC_PROJECTILE_05 "assets/textures/npc_projectile_texture_yellow.bmp"
# define NPC_PROJECTILE_06 "assets/textures/npc_projectile_texture_purple.bmp"

/*
** Hurt trigger definitions
*/

# define HURT_DMG 5

/*
** State defining how physics get applied for object / player
*/
typedef enum e_physics_state
{
	physics_state_falling = 1,
	physics_state_grounded = 2,
	physics_state_jumping = 3,
	physics_state_not_applied = 5,
}							t_physics_state;

/*
** A list defining what kind of objects the doom3d app contains in its scene /
** world. Each object has their own specific functionality, if any :)
** e.g. triggers react when player (or other) hit its bounding box (aabb),
** triggers can also be e.g. weapon drops.
** Default objects are just regular rendered 3d objects.
** t_3d_object
*/
typedef enum e_object_type
{
	object_type_default = 0,
	object_type_npc = 1,
	object_type_projectile = 2,
	object_type_trigger = 3,
	object_type_light = 4,
	object_type_path = 5,
}							t_object_type;

typedef enum e_light_type
{
	light_type_green = 11,
	light_type_yellow = 12,
	light_type_red = 13,
	light_type_blue = 14,
	light_type_cyan = 15,
	light_type_white = 17,
	light_type_explosion = 16,
}							t_light_type;

/*
** Prefab is a combination of assets, e.g. 3d model + texture + normal map.
** Or later a combination of 3d models and their textures.
** They are a bundle of things placeable by the editor.
*/
typedef enum e_prefab_type
{
	prefab_plane = 1,
	prefab_path_node = 2,
	prefab_window_wall = 3,
	prefab_lava_plane = 4
}							t_prefab_type;

/*
** Game object Params types
** ----------------------------
*/

/*
** Sub (params_type) for object_type_path
*/

typedef struct s_path_node
{
	t_bool		is_visited;
	float		global_goal;
	float		local_goal;
	int32_t		num_neighbors;
	t_3d_object	*neighbors[PATH_NEIGHBOUR_MAX];
	t_3d_object	*parent;
	t_3d_object	*parent_obj;
}							t_path_node;

/*
** A list of various trigger types
** t_trigger_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum e_trigger_type
{
	trigger_player_start = 1,
	trigger_player_end = 2,
	trigger_weapon_drop_shotgun = 3,
	trigger_weapon_drop_pistol = 4,
	trigger_weapon_drop_rpg = 5,
	trigger_item_jetpack,
	trigger_item_medkit,
	trigger_item_key,
	trigger_elevator_switch,
	trigger_door_switch,
	trigger_hurtbox,
	trigger_jukebox,
	trigger_type_disabled = 666,
}							t_trigger_type;

/*
** A list of npc types
** t_npc_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum e_npc_type
{
	npc_type_monster01,
	npc_type_monster01_a,
	npc_type_monster01_range,
	npc_type_monster02,
	npc_type_elevator,
	npc_type_crate,
	npc_type_boss,
}							t_npc_type;

/*
** A list of different projectiles that are used under weapons
** and also as their specific 3d objects.
** t_projectile_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum e_projectile_type
{
	projectile_type_rpg = 0,
	projectile_type_fireball,
	projectile_type_fireball_green,
	projectile_type_fireball_lgreen,
	projectile_type_fireball_pink,
	projectile_type_fireball_yellow,
	projectile_type_fireball_purple,
	projectile_type_bullet,
	projectile_type_none,
}							t_projectile_type;

/*
** ----------------------------
*/

/*
** Structs and enums defining data that may or may not belong
** inside t_3d_object->params or data that defines other game logic
** ----------------------------
*/

/*
** A list of weapons available for player
** These ids define e.g. which animation for player is used when shooting or
** reloading, or how player shoots in the game world.
*/

typedef enum e_weapon_id
{
	weapon_fist = 0,
	weapon_pistol = 1,
	weapon_shotgun = 2,
	weapon_rpg = 3,
}							t_weapon_id;

/*
** Weapon struct containing relevant data for player's world interaction
** with enemies.
*/

typedef struct s_weapon
{
	t_weapon_id				id;
	int						ammo;
	int						clip;
	int						clip_size;
	float					fire_rate;
	float					range;
	t_projectile_type		projectile;
	int						damage_per_hit;
}							t_weapon;

/*
** Projectile data defining how projectile objects are instantiated
** and how projectile interacts with the game world.
*/

typedef struct s_projectile
{
	t_projectile_type		type;
	int						damage;
	float					speed;
	float					range;
	float					traveled;
	float					radius;
	const char				*model_key;
	const char				*texture_key;
	const char				*normal_map_key;
	t_vec3					dir;
	t_vec3					euler_angles;
}							t_projectile;

/*
** a struct for triggers,
** mostly storing pointers to objects the trigger is linked to
*/

typedef struct s_trigger
{
	t_3d_object				*parent;
	t_3d_object				*linked_obj[MAX_TRIGGER_LINKS];
	int32_t					key_id;
	int32_t					num_links;
}							t_trigger;

/*
** Enum defining npc's state.
*/

typedef enum e_timer_type
{
	timer_switch,
	timer_end,
}							t_timer_type;

/*
** Enum defining npc's state.
*/

typedef enum e_npc_state
{
	state_idle,
	state_attack,
	state_atk_anim,
	state_death_anim,
	state_moving
}							t_npc_state;

/*
** Enum defining npc's attack pattern
*/

typedef enum e_npc_action
{
	action_wait,
	action_melee_basic,
	action_projectile_rpg,
	action_repeat,
	action_spawn_a,
	action_spawn_b,
}							t_npc_action;

/*
** NPC data defining how npc behaves in the world & how objects under npc
** are moved in the game world. Also defines how the npc t_3d_object
** gets instantiated.
*/

typedef struct s_npc
{
	t_3d_object				*parent;
	t_physics_state			physics_state;
	t_vec3					dir;
	float					angle;
	float					vision_range;
	float					hearing_range;
	int						interest;
	int						max_interest;
	t_bool					advance;
	float					atk_range;
	int						atk_dmg;
	uint32_t				atk_start;
	uint32_t				atk_dur;
	uint32_t				atk_timer;
	int						atk_pattern[MAX_ATTACK_PATTERN_SIZE];
	int						atk_pattern_index;
	t_3d_object				*patrol_path[MAX_PATROL_NODES + 1];
	int						patrol_path_index;
	int32_t					num_patrol_path_nodes;
	t_3d_object				*attack_path[MAX_PATH_NODE_NETWORK_SIZE + 1];
	int						attack_path_index;
	float					speed;
	float					rot_speed;
	float					dist;
	int						state;
	int						hp;
	int						type;
	t_vec3					velocity;
	float					model_scale;
	const char				*texture_key;
	const char				*model_key;
	const char				*normal_map_key;
	t_animation_3d			*animation_3d;
}							t_npc;

/*
** ----------------------------
*/

#endif
