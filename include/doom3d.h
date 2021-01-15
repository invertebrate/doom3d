/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/15 18:50:53 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOOM3D_H
# define DOOM3D_H

# include "libft.h"
# include "libgmatrix.h"
# include "lib3d.h"
# include <float.h>
# include "window.h"
# include <time.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define NUM_THREADS_DEFAULT 4
# define WIDTH 1280
# define HEIGHT 720
# define NAME "Doom3D"
# define PLAYER_SPEED 6.0
# define PLAYER_ROTATION_SPEED 0.2
# define NEAR_CLIP_DIST 10
# define FAR_CLIP_DIST 100000
# define MAX_NUM_OBJECTS 16384
# define MAX_ASSETS 64
# define MAX_LEVELS 16
# define TEMP_OBJECT_EXPIRE_SEC 100
# define NUM_WEAPONS 4

# define X_DIR 1
# define Y_DIR -1
# define Z_DIR 1

# define NPC_DEFAULT_MODEL "assets/models/box.obj"
# define NPC_DEFAULT_TEXTURE "assets/textures/rock.bmp"
# define NPC_DEFAULT_NORMM "assets/textures/rock.bmp"

typedef enum				e_object_type
{
	object_type_default = 0,
	object_type_npc = 1,
	object_type_projectile = 2,
	object_type_trigger = 3,
	object_type_item = 4,
}							t_object_type;

typedef enum				e_prefab_type
{
	prefab_plane = 1,
}							t_prefab_type;

typedef enum				e_trigger_type
{
	trigger_player_start = 1,
	trigger_player_end = 2,
	trigger_weapon_drop_shotgun = 3,
	trigger_weapon_drop_glock = 4,
	trigger_weapon_drop_rpg = 5,
}							t_trigger_type;

typedef enum				e_npc_type
{
	npc_type_default,
}							t_npc_type;

typedef enum				e_move
{
	move_forward,
	move_backward,
	move_strafe_left,
	move_strafe_right,
	move_down,
	move_up,
}							t_move;

typedef enum				e_scene_id
{
	scene_id_main_menu,
	scene_id_main_menu_settings,
	scene_id_main_game,
	scene_id_editor3d,
}							t_scene_id;

typedef enum				e_npc_state
{
	state_idle,
	state_attack,
	state_atk_anim,
	state_death_anim,
}							t_npc_state;

typedef enum				e_item_type
{
	item_type_weapon,
	item_type_key,
}							t_item_type;

typedef enum				e_weapon_id
{
	weapon_fist = 0,
	weapon_glock = 1,
	weapon_shotgun = 2,
	weapon_rpg = 3,
}							t_weapon_id;

typedef enum				e_projectile_type
{
	projectile_type_rpg = 0,
	projectile_type_bullet = 1,
	projectile_type_none = 2,
}							t_projectile_type;

typedef struct				s_weapon
{
	t_weapon_id				id;
	int						ammo;
	float					fire_rate;
	float					range;
	t_projectile_type		projectile;
	int						damage_per_hit;
}							t_weapon;


typedef struct				s_projectile
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
}							t_projectile;

typedef struct				s_camera
{
	t_vec3					origin;
	float					near_clip;
	float					far_clip;
	t_plane					viewplanes[6];
	t_plane					screen;
}							t_camera;

typedef struct				s_player
{
	t_vec3					pos;
	t_vec3					forward;
	t_vec3					sideways;
	t_vec3					up;
	t_bool					is_running;
	t_bool					is_shooting;
	t_bool					is_reloading;
	t_bool					is_moving;
	t_bool					is_rotating;
	float					speed;
	float					rot_speed;
	float					rot_x;
	float					rot_y;
	float					y_velocity;
	float					jump_force;
	t_bool					flying;
	float					player_height;
	float					fire_rate_per_sec;
	t_mat4					rotation;
	t_mat4					inv_rotation;
	t_mat4					translation;
	t_mat4					inv_translation;
	t_box3d					aabb;
	t_weapon				weapons[NUM_WEAPONS];
	t_weapon				*equipped_weapon;
	int						hp;
}							t_player;

typedef struct				s_asset_files
{
	const char				*animation_files[MAX_ASSETS];
	const char				*texture_files[MAX_ASSETS];
	const char				*normal_map_files[MAX_ASSETS];
	const char				*model_files[MAX_ASSETS];
	const char				*npc_names[MAX_ASSETS];
	const char				*prefab_names[MAX_ASSETS];
	const char				*trigger_names[MAX_ASSETS];
	uint32_t				num_animations;
	uint32_t				num_models;
	uint32_t				num_textures;
	uint32_t				num_normal_maps;
	uint32_t				num_npcs;
	uint32_t				num_prefabs;
	uint32_t				num_triggers;
}							t_asset_files;

typedef struct				s_scene
{
	t_3d_object				*objects[MAX_NUM_OBJECTS];
	uint32_t				num_objects;
	uint32_t				deleted_object_i[MAX_NUM_OBJECTS];
	uint32_t				num_deleted;
	int32_t					last_object_index;
	t_kd_tree				*triangle_tree;
	t_triangle				**triangle_ref;
	uint32_t				num_triangles;
	t_camera				*main_camera;
	t_triangle				*screen_triangles;
	t_button_group			**menus;
	uint32_t				num_button_menus;
	t_bool					is_paused;
	t_scene_id				scene_id;
	t_hash_table			*animation_textures;
	t_hash_table			*textures;
	t_hash_table			*normal_maps;
	t_hash_table			*models;
	t_hash_table			*npc_map;
	t_hash_table			*prefab_map;
	t_hash_table			*trigger_map;
	t_hash_table			*object_textures;
	t_hash_table			*object_normal_maps;
	t_asset_files			asset_files;
	t_surface				*skybox_textures[6];
	t_3d_object				*skybox[6];
	uint32_t				npc_update_timer;
}							t_scene;

typedef enum				e_editor_menu_index
{
	editor_menu_none = 0,
	editor_menu_prefabs = 1,
	editor_menu_objects = 2,
	editor_menu_textures = 3,
	editor_menu_normalmaps = 4,
	editor_menu_npcs = 5,
	editor_menu_triggers = 6,
}							t_editor_menu_index;

typedef struct s_npc		t_npc;

typedef struct 				s_editor
{
	t_bool					is_saving;
	t_bool					is_saved;
	t_bool					is_moving;
	t_editor_menu_index		editor_menu_id;
	t_button_menu			*editor_menu;
	int32_t					editor_level;
	char					editor_filename[128];
	char					editor_savename[128];
	char					selected_object_str[128];
	t_3d_object				*selected_object;
}							t_editor;

typedef struct				s_settings
{
	t_bool					is_normal_map;
	t_bool					is_skybox;
}							t_settings;

typedef enum				e_nofitication_type
{
	notification_type_info,
	notification_type_story,
}							t_notification_type;
typedef struct				e_notification
{
	const char				*message;
	t_notification_type		type;
	int32_t					time;
}							t_notification;

typedef struct				s_anim_frame
{
	int32_t		x_offset;
	int32_t		y_offset;
	int32_t		width;
	int32_t		height;
}							t_anim_frame;

typedef struct				s_sprite_anim
{
	uint32_t				id;
	t_anim_frame			frames[16];
	int32_t					num_frames;
	int32_t					current_frame;
	int32_t					frame_time;
	int32_t					frame_time_left;
	t_bool					interruptable;
	t_bool					is_finished;
}							t_sprite_anim;

typedef enum				e_player_animation
{
	anim_none = 0,
	anim_shotgun_default = 1,
	anim_shotgun_shoot = 2,
	anim_shotgun_reload = 3,
	anim_glock_default = 4,
	anim_glock_shoot = 5,
	anim_glock_reload = 6,
}							t_player_animation;

typedef struct				s_player_hud
{
	t_player_animation		curr_animation;
}							t_player_hud;

typedef struct				s_doom3d
{
	t_bool					is_running;
	t_bool					is_debug;
	t_bool					is_first_render;
	t_bool					is_scene_reload;
	t_info					info;
	t_window				*window;
	t_scene_id				next_scene_id;
	t_scene					*active_scene;
	t_player				player;
	t_player_hud			player_hud;
	t_mouse					mouse;
	t_keyboard				keyboard;
	t_thread_pool			*thread_pool;
	float					unit_size;
	int32_t					triangles_in_view;
	char					*level_list[MAX_LEVELS];
	uint32_t				num_levels;
	uint32_t				current_level;
	t_editor				editor;
	t_settings				settings;
	t_list					*notifications;
	t_projectile			projectile_data[1];
	t_weapon				weapons_data[NUM_WEAPONS];
	t_sprite_anim			animations[16];
}							t_doom3d;

struct						s_npc
{
	t_vec3					dir;
	float					angle;
	float					vision_range;
	float					atk_range;
	int						atk_dmg;
	uint32_t				atk_start;
	uint32_t				atk_dur;
	uint32_t				atk_timer;
	float					speed;
	float					rot_speed;
	float					dist;
	int						state;
	int						hp;
	int						type;
	float					y_velocity;
	const char				*texture_key;
	const char				*model_key;
	const char				*normal_map_key;
};

/*
** For parallelization
*/

typedef struct				s_render_work
{
	t_doom3d				*app;
	t_framebuffer			*framebuffer;
	uint32_t				sub_buffer_i;
	t_tri_vec				*render_triangles;
}							t_render_work;

typedef struct				s_button_menu_params
{
	const char				**button_names;
	int32_t					num_buttons;
	void					(*on_click)(t_button *, void *);
	TTF_Font				*button_font;
}							t_button_menu_params;

void						doom3d_run(t_doom3d *app);

/*
** Player
*/
void						player_init(t_doom3d *app, t_vec3 pos);
void						player_move(t_doom3d *app, t_move dir, float speed);
void						player_rotate_vertical(t_doom3d *app, float angle);
void						player_rotate_horizontal(t_doom3d *app,
								float angle);
void						player_apply_gravity(t_doom3d *app);
void						collision_limit_player(t_doom3d *app, t_vec3 add);
void						player_update_aabb(t_player *player);
void						editor_vertical_move(t_doom3d *app, float speed);
void						player_shoot_projectile(t_doom3d *app, t_vec3 origin);
void						player_shoot_ray(t_doom3d *app,
								t_vec3 origin, t_vec3 dir);
void						player_onhit(t_doom3d *app, int damage);
void						player_jump(t_doom3d *app);

/*
** Inventory
*/

void						weapons_init(t_doom3d *app);
void						weapons_init_data(t_doom3d *app);
void						weapon_equip(t_doom3d *app, t_weapon_id slot);
void						inventory_pickup_weapon_object(t_doom3d *app,
								t_3d_object *weapon_drop_obj);
void						inventory_throw_weapon(t_doom3d *app);

t_weapon					weapon_data_fist(t_doom3d *app);
t_weapon					weapon_data_glock(t_doom3d *app);
t_weapon					weapon_data_rpg(t_doom3d *app);
t_weapon					weapon_data_shotgun(t_doom3d *app);

/*
** Projectile
*/

void						projectile_data_init(t_doom3d *app);
t_projectile				projectile_data_rpg(t_doom3d *app);
void						projectile_update(t_doom3d *app, t_3d_object *obj);
void						projectile_explosion(t_doom3d *app, t_vec3 pos, t_projectile *projectile);

/*
** Npc
*/

void						npc_spawn(t_doom3d *app, t_vec3 pos, float angle,
								int type);
void						npc_update(t_doom3d *app, t_3d_object *npc_obj);
void						npc_execute_behavior(t_doom3d *app,
								t_3d_object *npc_obj);
void						npc_default(t_doom3d *app, t_npc *npc);
void						handle_npc_deletions(t_doom3d *app);
void						parse_npc_type(t_doom3d *app, t_npc *npc, int type);
void						npc_trigger_onhit(t_doom3d *app, t_3d_object *obj, int damage);

/*
** Physics
*/

t_bool						obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj);
t_bool						player_is_grounded(t_doom3d *app);
void						gravity_update(t_doom3d *app, t_3d_object *tested);

/*
** Events
*/
void						doom3d_events_handle(t_doom3d *app);
void						mouse_state_handle(t_doom3d *app);
void						player_shoot(t_doom3d *app,
								uint32_t curr_time);
void						keyboard_state_handle(t_doom3d *app);
void						general_input_events_handle(t_doom3d *app,
								SDL_Event event);
void						handle_editor_selection(t_doom3d *app,
								SDL_Event event);
void						handle_editor_saving(t_doom3d *app,
								SDL_Event event);
t_bool						editor_popup_menu_open(t_doom3d *app);

/*
** Camera
*/
t_camera					*new_camera(void);
void						update_camera(t_doom3d *app);

/*
** Rendering
*/
t_bool						screen_intersection(t_doom3d *app,
								t_triangle *triangle);
t_bool						is_rendered(t_doom3d *app, t_triangle *triangle);
void						ui_render(t_doom3d *app);
void						doom3d_render(t_doom3d *app);
void						loading_render(t_doom3d *app);
t_tri_vec					*prepare_render_triangles(t_doom3d *app);
void						destroy_render_triangles(
								t_tri_vec *render_triangles);
void						clip_and_add_to_render_triangles(t_doom3d *app,
								t_tri_vec *r_triangle_vec,
								t_triangle *triangle);
void						rasterize_triangles(t_render_work *work);
t_bool						triangle_inside_viewbox(t_doom3d *app,
								t_triangle *triangle);
t_bool						triangle_too_far(t_doom3d *app,
								t_triangle *triangle);
void						prepare_skybox_render_triangle(t_doom3d *app,
								t_triangle *r_triangle,
								t_triangle *triangle, t_vertex *vtc);
void						prepare_render_triangle(t_doom3d *app,
								t_triangle *r_triangle,
								t_triangle *triangle, t_vertex *vtc);
t_bool						object_inside_viewbox(t_doom3d *app,
								t_3d_object *obj);
void						hud_render(t_doom3d *app);
void						framebuffer_dark_overlay(
								t_framebuffer *framebuffer,
								int32_t width, int32_t height, t_vec2 pos);
void						set_aabb_origin_to_corners(t_3d_object *obj,
								t_vec3 origin, t_vec3 origin_to_corner[8]);
void						button_menu_render(t_button_group *menu, t_vec2 pos);
void						editor_ui_render(t_doom3d *app);
void						draw_debug_line(t_doom3d *app,
								t_sub_framebuffer *buffer, t_vec3 points[2],
								uint32_t color);
void						draw_editor_debug_grid(t_render_work *work);
void						draw_selected_wireframe(t_render_work *work);
t_bool						triangle_outside_frame(t_triangle *triangle,
								t_sub_framebuffer *sub_buffer);
void						draw_selected_aabb(t_render_work *work);
void						draw_selected_enemy_direction(t_render_work *work);
void						notifications_render(t_doom3d *app, t_vec2 pos);
void						draw_triangle_tree_bounding_boxes(
								t_render_work *work);

/*
** Objects
*/
void						doom3d_update_objects(t_doom3d *app);
void						object_type_to_str(t_3d_object *obj, char *str);
t_3d_object					*find_one_object_by_type(t_doom3d *app,
								uint32_t object_type,
								uint32_t param_type);

/*
** Scene
*/
void						scene_assets_load(t_scene *scene);
void						active_scene_content_set(t_doom3d *app);
void						active_scene_update_after_objects(t_scene *scene);
t_scene						*scene_new(t_scene_id scene_id);
void						scene_destroy(t_doom3d *app);
void						scene_next_select(t_doom3d *app);
void						scene_debug(t_scene *scene);
void						scene_map_init(t_scene *scene);
void						scene_camera_destroy(t_scene *scene);
void						scene_objects_destroy(t_scene *scene);
void						scene_skybox_destroy(t_scene *scene);
void						scene_assets_destroy(t_scene *scene);
void						scene_textures_destroy(t_scene *scene);
void						scene_normal_maps_destroy(t_scene *scene);
void						active_scene_popup_menu_destroy(t_doom3d *app);

/*
** Editor
*/
void						save_map(t_doom3d *app);
void						read_map(t_doom3d *app, const char *map_name);
const char					*normal_map_file_key(char *filename, t_doom3d *app);
const char					*texture_file_key(char *filename, t_doom3d *app);
void						place_scene_object(t_doom3d *app,
								const char *filenames[3],
								t_vec3 pos);
void						object_set_for_deletion(t_doom3d *app,
								t_3d_object *object);
void						place_procedural_scene_object(t_doom3d *app,
								t_3d_object *model,
								const char *filenames[2], t_vec3 pos);
void						editor_select(t_doom3d *app);
void						editor_deselect_all(t_doom3d *app);
void						editor_deselect(t_doom3d *app);
void						after_editor_transform(t_doom3d *app,
								uint32_t *last_changed);
void    					editor_init(t_doom3d *app, int32_t editor_level);

/*
** Level
*/
void						read_level_list(t_doom3d *app);

/*
** Menus
*/
t_button_group				*button_menu_create(t_doom3d *app,
								t_button_menu_params menu_params);
void						main_menu_create(t_doom3d *app);
void						editor3d_menu_create(t_doom3d *app);
void						pause_menu_create(t_doom3d *app);
void						settings_menu_create(t_doom3d *app);
void						active_scene_menu_recreate(t_doom3d *app);
void						scene_menus_destroy(t_scene *scene);

/*
** Utils
*/
void						doom3d_debug_info_render(t_doom3d *app);
void						doom3d_debug_info_capture(t_doom3d *app);
uint64_t					doom3d_performance_counter_start(void);
void						doom3d_performance_counter_end(uint64_t start_time,
								char *task_name, float delta_limit);
void						doom3d_notification_add(t_doom3d *app,
								t_notification notification);
void						doom3d_notifications_update(t_doom3d *app);
void						doom3d_notifications_delete_all(t_doom3d *app);

/*
** Triggers
*/
void						place_player_end(t_doom3d *app);
void						place_player_start(t_doom3d *app);
void						place_drop_shotgun(t_doom3d *app);
void						editor_triggers_unhighlight(t_doom3d *app);
void						editor_triggers_highlight(t_doom3d *app);

/*
** Player animations
*/
void						player_animations_init(t_doom3d *app);
void						doom3d_player_animation_update(t_doom3d *app);
void						set_player_shoot_frame(t_doom3d *app);
void						set_player_reload_frame(t_doom3d *app);
void						set_player_default_frame(t_doom3d *app);
t_surface					*get_animation_source(t_doom3d *app);

#endif
