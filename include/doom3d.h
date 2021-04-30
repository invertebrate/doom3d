/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/30 21:28:28 by ohakola          ###   ########.fr       */
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

/*
** Doom3d specific includes
*/

# include "game_objects.h"
# include "player.h"
# include "scene.h"
# include "editor.h"
# include "notification.h"
# include "sprite_animation.h"
# include "animations_3d.h"
# include "sound.h"
# include "events.h"

/*
** ------------------------
*/

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

/*
** Number of cores is read by SDL, but this is a backup macro if there are
** not enough cores on the user's chip. Means how many threads is used
** by the threadpool.
*/

# define NUM_THREADS_DEFAULT 4

/*
** Initial dimensions for the screen, these can be edited at runtime.
** Options: 1920x1080, 1280x720 and 960x540
*/

# define WIDTH 960
# define HEIGHT 540
# define NAME "Doom3D"

# define GAME_VIEW_DIST_UNITS 200
# define EDITOR_VIEW_DIST_UNITS 500

/*
** Allocation space for render triangles used in rasterization
** Increase if needed (error encountered)
*/

# define RENDER_TRIANGLE_POOL_SIZE 131072

/*
** Defines how many levels can be created, otherwise the app will remind
** that too many levels were created.
*/

# define MAX_LEVELS 16

/*
** Defines the directions of our coordinate system. Touching this will without
** doubt mess things up, so don't switch. This is more like an informative
** place to see what which direction means in our coordinate system.
*/

# define X_DIR 1
# define Y_DIR -1
# define Z_DIR 1

# define CONST_SPEED 0.1
# define CONST_GRAVITY 2.0

/*
** How often to update forces? Don't make smaller ms than frame delta time
*/

# define FORCES_UPDATE_MS 100

# define NUM_CUSTOM_EVENTS 64
# define MAX_TIMERS 16

typedef struct				s_settings
{
	t_bool					is_normal_map;
	t_bool					is_skybox;
	int32_t					width;
	int32_t					height;
}							t_settings;

typedef struct				s_timer
{
	t_bool					active;
	t_3d_object				*target;
	int						timer_end;
}							t_timer;

typedef struct				s_patrol_path_vars
{
	t_3d_object		*obj;
	t_npc			*npc;
	uint32_t		object_id;
	int32_t			num_patrol_path_nodes;
}							t_patrol_path_vars;

typedef struct				s_trigger_link_vars
{
	t_3d_object		*obj;
	t_trigger		*trigger;
	uint32_t		object_id;
	int32_t			num_trigger_links;
}							t_trigger_link_vars;

/*
** Main struct, "The App".
*/

typedef struct				s_doom3d
{
	t_bool					is_running;
	t_bool					is_debug;
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
	uint64_t				current_tick;
	t_settings				settings;
	t_list					*notifications;
	char					action_text[1024];
	t_path_node				*path_node_network[MAX_PATH_NODE_NETWORK_SIZE + 1];
	int						path_node_network_count;
	t_projectile			projectile_data[NUM_PROJECTILES];
	t_weapon				weapons_data[NUM_WEAPONS];
	t_sprite_anim			animations[NUM_PLAYER_ANIMATIONS];
	t_mp					mp;
	uint32_t				custom_event_type;
	t_hash_table			*custom_event_handles;
	t_triangle				*render_triangle_pool;
	t_vertex				*render_vertex_pool;
	uint32_t				num_render_triangles;
	uint32_t				num_render_vertices;
	uint32_t				render_triangle_pool_size;
	uint32_t				render_vertex_pool_size;
	t_timer					timer[MAX_TIMERS];
}							t_doom3d;

/*
** For parallelized rendering. See documentation.md
** Each thread has their reference to a sub frame buffer (a square)
** that then afterwards get placed onto main buffer. Each line or triangle
** gets cut and data outside thread's sub buffer is ignored (Culling).
*/

typedef struct				s_render_work
{
	t_doom3d				*app;
	t_framebuffer			*framebuffer;
	uint32_t				sub_buffer_i;
	t_tri_vec				*render_triangles;
	uint32_t				pass;
	uint32_t				num_passes;
}							t_render_work;

void						doom3d_run(t_doom3d *app);
void						settings_init(t_doom3d *app);

/*
** Player
*/
void						update_player(t_doom3d *app);
void						player_init(t_doom3d *app, t_vec3 pos);
void						player_flashlight_init(t_doom3d *app,
													t_player *player);
void						player_flashlight_update(t_player *player);
void						player_move(t_doom3d *app);
void						get_move_dir(t_doom3d *app,
								t_move dir_option, t_vec3 dir);
void						player_rotate_vertical(t_doom3d *app, float angle);
void						player_rotate_horizontal(t_doom3d *app,
								float angle);
void						player_apply_gravity(t_doom3d *app);
void						collision_limit_player_horizontal(t_doom3d *app,
															t_vec3 add);
void						player_update_aabb(t_player *player);
void						player_onhit(t_doom3d *app, int damage);
void						player_jump(t_doom3d *app);
void						player_crouch(t_doom3d *app, t_bool toggle);
void						player_shoot(t_doom3d *app,
								uint32_t curr_time);
void						player_reload(t_doom3d *app);
void						player_reload_finish(t_doom3d *app);
void						player_interact(t_doom3d *app);

/*
** Player items
*/

void						weapons_init(t_doom3d *app);
void						weapons_init_data(t_doom3d *app);
void						weapon_equip(t_doom3d *app, t_weapon_id slot);
void						inventory_pickup_weapon_object(t_doom3d *app,
								t_3d_object *weapon_drop_obj);
void						inventory_pickup_key(t_doom3d *app,
												t_3d_object *key_obj);
void						inventory_pickup_medkit(t_doom3d *app,
													t_3d_object *medkit_obj);
t_weapon					weapon_data_fist(t_doom3d *app);
t_weapon					weapon_data_pistol(t_doom3d *app);
t_weapon					weapon_data_rpg(t_doom3d *app);
t_weapon					weapon_data_shotgun(t_doom3d *app);

/*
** Projectiles
*/

void						projectile_data_init(t_doom3d *app);
t_projectile				projectile_data_rpg(t_doom3d *app);
t_projectile				projectile_data_fireball(t_doom3d *app);
t_projectile				projectile_data_fireball_custom(t_doom3d *app,
															int type);
void						projectile_update(t_doom3d *app, t_3d_object *obj);
void						projectile_explosion(t_doom3d *app, t_vec3 pos,
								t_projectile *projectile);
void						place_projectile_object_in_scene(t_doom3d *app,
								t_projectile *projectile, t_vec3 origin,
															t_vec3 rot);

/*
** Npcs
*/

t_3d_object					*npc_spawn(t_doom3d *app, t_vec3 pos, float angle,
								int type);
void						npc_update_state(t_doom3d *app,
											t_3d_object *npc_obj);
void						npc_execute_behavior(t_doom3d *app,
												t_3d_object *npc_obj);
void						npc_default(t_doom3d *app, t_npc *npc,
										t_3d_object *obj);
void						npc_monster01(t_doom3d *app, t_npc *npc, int type);
void						npc_ranged(t_doom3d *app, t_npc *npc,
										t_3d_object *obj);
void						npc_elevator(t_doom3d *app, t_npc *npc,
										t_3d_object *obj);
void						npc_crate(t_doom3d *app, t_npc *npc,
										t_3d_object *obj);
void						handle_npc_deletions(t_doom3d *app);
void						parse_npc_type(t_doom3d *app, t_npc *npc, int type);
void						npc_trigger_onhit(t_doom3d *app,
								t_3d_object *obj, int damage);
void						npc_get_dir_to_next_waypoint(t_doom3d *app,
														t_3d_object *obj);
t_bool						npc_get_dir_to_next_attack_waypoint(t_doom3d *app,
															t_3d_object *obj);
void						npc_move_step_to_waypoint(t_doom3d *app,
														t_3d_object *obj);
void						elevator_go_to_next_node(t_doom3d *app,
														t_3d_object *obj);
t_bool						npc_has_line_of_sight(t_doom3d *app,
												t_3d_object *npc_obj);
void						path_node_network_init(t_doom3d *app);
void						npc_find_path(t_doom3d *app, t_npc *npc,
											t_vec3	start, t_vec3 end);
t_bool						npc_destroy(t_3d_object *npc_obj);
void						check_npc_hearing(t_doom3d *app, t_vec3 hit);

/*
** Physics
*/

t_bool						obj_is_grounded(t_doom3d *app,
											t_3d_object *falling_obj);
t_bool						player_is_grounded(t_doom3d *app);
t_bool						should_nudge_to_ground(t_doom3d *app);
t_bool						player_hits_ceiling(t_doom3d *app);
void						nudge_player_off_ceiling(t_doom3d *app);
void						update_object_forces(t_doom3d *app,
								t_3d_object *tested);
void						update_object_physics_state(t_doom3d *app,
								t_3d_object *obj);
void						forces_update_player(t_doom3d *app);
t_3d_object					*object_under(t_doom3d *app,
											t_vec3 origin, uint32_t self_id,
											t_vec3 hit_point);
t_3d_object					*object_above(t_doom3d *app,
											t_vec3 origin, uint32_t self_id,
											t_vec3 hit_point);
t_bool						obj_is_grounded(t_doom3d *app,
											t_3d_object *falling_obj);

/*
** Events
*/

void						push_custom_event(t_doom3d *app,
												t_doom3d_event code,
												void *data1,
												void *data2);
void						register_custom_events(t_doom3d *app);
void						register_editor_custom_events(t_doom3d *app);
void						register_player_custom_events(t_doom3d *app);
void						player_custom_event_to_str(char *str,
														t_doom3d_event code);
void						editor_custom_event_to_str(char *str,
														t_doom3d_event code);
void						handle_custom_events(t_doom3d *app,
								SDL_Event event);
void						handle_player_rotation_input(t_doom3d *app,
								int32_t xrel, int32_t yrel);
void						handle_events(t_doom3d *app);
void						handle_mouse_state_input(t_doom3d *app);
void						handle_editor_mouse_state_input(t_doom3d *app);
void						handle_keyboard_state_input(t_doom3d *app);
void						handle_editor_transform_input(t_doom3d *app);
void						handle_editor_keyboard_state_input(t_doom3d *app);
void						handle_control_flow_events(t_doom3d *app,
								SDL_Event event);
void						handle_editor_input_events(t_doom3d *app,
								SDL_Event event);
t_bool						editor_popup_menu_open(t_doom3d *app);
t_bool						editor_popup_menu_open(t_doom3d *app);
t_bool						mouse_inside_editor_view(t_doom3d *app);
t_3d_object					*editor_object_by_mouse(t_doom3d *app);
void						editor_point_on_target(t_doom3d
								*app, t_vec3 hit_point);

/*
** Custom Event handling
*/

void						register_object_custom_events(t_doom3d *app);
void						object_custom_event_to_str(char *str,
								t_doom3d_event code);
int							handle_play_effect(t_doom3d *app,
								int ind, t_sound *new);
int							handle_play_music(t_doom3d *app,
								int ind, t_sound *new);
void						handle_object_deletion(t_doom3d *app,
								t_3d_object *object);
void						handle_object_translate_x(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_object_translate_y(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_object_translate_z(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_object_scale(t_doom3d *app,
												t_3d_object *object,
												int32_t direction);
void						handle_object_scale_with_uvs(t_doom3d *app,
														t_3d_object *object,
														int32_t dir);
void						handle_object_rotate_x(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_object_rotate_y(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_object_rotate_z(t_doom3d *app,
													t_3d_object *object,
													int32_t amount);
void						handle_window_resize(t_doom3d *app,
												uint32_t width,
												uint32_t height);
void						handle_scene_change(t_doom3d *app,
												t_scene_id scene_id);
void						handle_scene_reload(t_doom3d *app);
void						handle_quit(t_doom3d *app);
void						handle_editor_placement_end(t_doom3d *app);
void						handle_editor_placement_cancel(t_doom3d *app);
void						handle_editor_placement_start(t_doom3d *app,
														uint32_t obj_type,
														void *data);
void						handle_editor_in_placement_move(t_doom3d *app);
void						handle_editor_save_end(t_doom3d *app);
void						handle_editor_save_start(t_doom3d *app);
void						handle_editor_save_type_backspace(t_doom3d *app);
void						handle_editor_save_type(t_doom3d *app, char *text);
void						handle_editor_delete(t_doom3d *app);
void						handle_editor_exit(t_doom3d *app);
void						handle_editor_deselect(t_doom3d *app);
void						handle_editor_deselect_all(t_doom3d *app);
void						handle_editor_select(t_doom3d *app);
void						handle_editor_level_switch(t_doom3d *app);
void						handle_editor_open_popup_menu(t_doom3d *app,
								t_editor_menu_index menu_id, t_vec3 pos);
void						handle_editor_key_input2(t_doom3d *app,
													SDL_Event event);
void						handle_editor_flip_lights(t_doom3d *app);
void						handle_editor_add_texture(t_doom3d *app,
														char *filename);
void						handle_editor_add_normal_map(t_doom3d *app,
														char *filename);
void						handle_editor_zoom(t_doom3d *app,
												int32_t zoom_amount);
void						handle_editor_toggle_vertical_lock(t_doom3d *app);
void						handle_editor_move_view_forward(t_doom3d *app,
															int32_t amount);
void						handle_editor_move_view_sideways(t_doom3d *app,
															int32_t amount);
void						handle_editor_rotate_view(t_doom3d *app,
														int32_t xrel,
														int32_t yrel);
void						handle_editor_duplication(t_doom3d *app);
void						handle_editor_patrol_slot_decrement(t_doom3d *app);
void						handle_editor_patrol_slot_increment(t_doom3d *app);
void						handle_editor_snap_to_grid(t_doom3d *app);
void						handle_toggle_pause_game(t_doom3d *app);
void						handle_toggle_fullscreen(t_doom3d *app);
void						handle_toggle_normal_map_mode(t_doom3d *app);
void						handle_toggle_debug_mode(t_doom3d *app);
void						handle_player_toggle_flight(t_doom3d *app);
void						handle_player_jump(t_doom3d *app);
void						handle_player_move(t_doom3d *app,
											t_move move_dir,
											int32_t amount);
void						handle_player_rotate(t_doom3d *app, int32_t xrel,
												int32_t yrel);
void						handle_player_crouch(t_doom3d *app,
												t_bool is_crouching);
void						handle_player_weapon_equip(t_doom3d *app,
													t_weapon_id weapon);
void						handle_player_reload(t_doom3d *app);
void						handle_player_shoot(t_doom3d *app);
void						handle_player_interact(t_doom3d *app);

/*
** 3D Animations
*/

void						npc_animation_3d_set(t_doom3d *app,
												t_3d_object *obj, t_npc *npc,
												t_anim_metadata *anim_data);
void						npc_animation_3d_init(t_doom3d *app,
												t_3d_object *obj);
void						update_app_ticks(t_doom3d *app);
uint32_t					anim_3d_frame_update(t_doom3d *app,
												t_animation_3d *animation);
uint32_t					anim_3d_clip_loop(t_doom3d *app, t_3d_object *obj,
											t_animation_3d_type clip,
											uint32_t start_frame);
t_bool						anim_3d_clip_play(t_doom3d *app, t_3d_object *obj,
											t_anim_3d_instance *anim_instance);
void						npc_anim_3d_position_update(t_animation_3d *anim);
void						npc_anim_3d_rotation_update(t_animation_3d *anim);
t_bool						check_obj_3d_anim(t_3d_object *obj);
t_bool						animation_3d_instance_destroy(t_anim_3d_instance
														*instance);
void						npc_anim3d_material_copy(t_3d_object *source,
													t_3d_object *dest);
void						init_anim_instance(t_doom3d *app,
											t_anim_3d_instance *anim_instance);
void						npc_animation_3d_data_copy(t_npc *npc,
														t_anim_metadata
														*anim_data);
t_bool						frame_time_expired(t_doom3d *app,
												t_animation_3d *animation);
t_bool						anim_3d_clip_ended(t_animation_3d *animation);
t_bool						instance_status_check(t_animation_3d *animation,
												float elapsed_time);
void						copy_instance_data(t_animation_3d *anim,
												t_anim_3d_instance *instance);
uint32_t					npc_anim_3d_transform_update(t_animation_3d
														*animation);
void						init_anim_instance_death(t_3d_object *obj,
													t_anim_3d_instance *inst);
void						init_anim_instance_attack(t_3d_object *obj,
													t_anim_3d_instance *inst);

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
void						render_ui(t_doom3d *app);
void						render_ui_title(t_doom3d *app);
void						render_button_menu(t_button_group *menu,
								t_vec2 pos);
void						framebuffer_dark_overlay(
								t_framebuffer *framebuffer);
void						framebuffer_health_low_overlay(
								t_doom3d *app);
void						render_loading_view(t_doom3d *app);
void						render_to_framebuffer(t_doom3d *app);
void						render_work(void *params);
void						render_parallel_3d_view(t_doom3d *app,
								t_framebuffer *framebuffer);
void						render_loading_view(t_doom3d *app);
t_tri_vec					**prepare_render_triangles(t_doom3d *app);
t_bool						object_too_far(t_doom3d *app, t_3d_object *obj);
void						add_skybox_render_triangles(t_doom3d *app,
								t_tri_vec **render_triangles);
void						add_objects_render_triangles(t_doom3d *app,
								t_tri_vec **render_triangles);
void						add_temp_object_render_triangles(t_doom3d *app,
								t_tri_vec **render_triangles);
void						sort_render_triangles_by_depth(t_doom3d *app,
								t_tri_vec **render_triangles,
								int32_t skybox_offset);
void						destroy_render_triangle_vecs(
								t_tri_vec **render_triangles);
void						clip_and_add_to_render_triangles(t_doom3d *app,
								t_tri_vec **r_triangle_vecs,
								t_triangle *triangle);
void						rasterize_triangles(t_render_work *work);
void						rasterize_triangles_transparent(t_render_work
								*work);
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
void						render_hud(t_doom3d *app);
void						set_aabb_origin_to_corners(t_3d_object *obj,
								t_vec3 origin, t_vec3 origin_to_corner[8]);
void						render_button_menu(t_button_group *menu,
								t_vec2 pos);
void						render_editor_ui(t_doom3d *app);
void						render_object_information(t_doom3d *app);
void						draw_debug_line(t_doom3d *app,
								t_sub_framebuffer *buffer, t_vec3 points[2],
								uint32_t color);
void						draw_editor_debug_grid(t_render_work *work);
void						draw_selected_wireframe(t_render_work *work);
t_bool						triangle_outside_frame(t_triangle *triangle,
								t_sub_framebuffer *sub_buffer);
void						draw_selected_aabb(t_render_work *work);
void						draw_selected_enemies_direction(t_render_work
															*work);
void						draw_enemy_direction(t_doom3d *app,
								t_sub_framebuffer *sub_buffer,
								t_3d_object *npc_object);
void						draw_npc_dirs(t_render_work *work);
void						render_notifications(t_doom3d *app, t_vec2 pos);
void						render_notification_messages(t_doom3d *app,
								t_vec2 pos,
								int32_t	text_dims[2], int32_t padding);
void						render_notifications_background(t_doom3d *app,
								t_vec2 pos,
								int32_t	dims[2], int32_t border_size);
void						draw_triangle_tree_bounding_boxes(
								t_render_work *work);
void						draw_editor_placement_position(t_render_work *work);
t_triangle					*get_render_triangle_from_pool(t_doom3d *app);
void						destroy_render_triangle_pool(t_doom3d *app);
void						reset_render_triangle_pool(t_doom3d *app);
void						allocate_render_triangle_pool(t_doom3d *app,
								uint32_t size);
void						calculate_final_luminosity(uint32_t *pixel,
														uint32_t *light);

/*
** Objects
*/

void						update_light_sources(t_doom3d *app,
								t_3d_object *object);
void						update_light_sources_anim3d(t_doom3d *app,
														t_3d_object *object);
void						transform_light_pos(t_doom3d *app, t_vec3 light_pos,
												int32_t object_i);
void						update_one_light_source(t_doom3d *app,
													t_3d_object *object,
													float radius_intensity[2],
													int32_t i);
void						update_editor_light_sources(t_doom3d *app);
void						update_objects(t_doom3d *app);
void						object_type_to_str(t_3d_object *obj, char *str);
t_3d_object					*find_one_object_by_type(t_doom3d *app,
								uint32_t object_type,
								uint32_t param_type);
void						path_objects_set_neighbors(t_doom3d *app);
t_3d_object					*find_object_by_id(t_doom3d *app, uint32_t id);

/*
** Scene
*/

void						load_sprite_animations_to_memory(t_scene *scene,
								t_asset_files *data);
void						prefabs_load(t_scene *scene);
void						triggers_load(t_scene *scene);
void						lights_load(t_scene *scene);
void						npcs_load(t_scene *scene);
void						load_skybox_textures_to_memory(t_scene *scene);
void						load_animation_3d_frames_to_memory(t_scene *scene,
								t_asset_files *data);
void						scene_animation_sprite_files_set(t_asset_files
								*data);
void						scene_texture_files_set(t_asset_files *data);
void						scene_model_files_set(t_asset_files *data);
void						scene_animation_3d_files_set(t_asset_files *data);
void						scene_normal_map_files_set(t_asset_files *data);
void						scene_assets_load(t_scene *scene);
void						active_scene_content_set(t_doom3d *app);
void						active_scene_update_after_objects(t_scene *scene);
t_scene						*scene_new(t_scene_id scene_id);
void						scene_destroy(t_doom3d *app);
void						select_next_scene(t_doom3d *app);
void						scene_map_init(t_scene *scene);
void						scene_camera_destroy(t_scene *scene);
void						scene_objects_destroy(t_scene *scene);
void						scene_skybox_destroy(t_scene *scene);
void						scene_assets_destroy(t_scene *scene);
void						scene_textures_destroy(t_scene *scene);
void						scene_normal_maps_destroy(t_scene *scene);
void						active_scene_popup_menu_destroy(t_doom3d *app);
void						extend_all_objects_shading_opts(t_doom3d *app,
								t_shading_opts opts_to_add);
void						remove_all_objects_shading_opts(t_doom3d *app,
								t_shading_opts opts_to_remove);
void						finish_level(t_doom3d *app);

/*
** Editor
*/

void						editor_objects_invisible_unhighlight(t_doom3d *app);
void						editor_objects_invisible_highlight(t_doom3d *app);
void						write_trigger_link_information(int32_t fd,
								t_doom3d *app);
void						write_npc_patrol_path_information(int32_t fd,
								t_doom3d *app);
void						write_path_object_information(int32_t fd,
								t_doom3d *app);
void						write_key_ids(int32_t fd, t_doom3d *app);
void						save_map(t_doom3d *app);
void						write_savename_to_level_list(t_doom3d *app);
int32_t						read_key_id_information(t_doom3d *app,
								char *contents);
int32_t						read_objects(t_doom3d *app, char *contents);
int32_t						read_path_nodes(t_doom3d *app,
								char *contents);
int32_t						read_path_node_npc_links(t_doom3d *app,
								char *contents);
int32_t						read_npc_path(t_doom3d *app,
								char *contents, int32_t offset);
int32_t						read_trigger_link_information(t_doom3d *app,
								char *contents);
int32_t						get_num_npcs(t_doom3d *app);
int32_t						get_num_path_nodes(t_doom3d *app);
float						pitch_from_rotation_matrix(t_mat4 rotation);
int32_t						read_obj_normal_map(t_3d_object *obj,
								t_doom3d *app, char *contents);
int32_t						read_obj_texture(t_3d_object *obj,
								t_doom3d *app, char *contents);
void						read_map(t_doom3d *app, const char *map_name);
const char					*normal_map_file_key(char *filename, t_doom3d *app);
const char					*texture_file_key(char *filename, t_doom3d *app);
t_3d_object					*place_scene_object(t_doom3d *app,
												const char *filenames[3],
												t_vec3 pos);
t_3d_object					*place_procedural_scene_object(t_doom3d *app,
													t_3d_object *model,
													const char *filenames[2],
													t_vec3 pos);
t_3d_object					*place_temp_object(t_doom3d *app,
												const char *filenames[3],
												t_vec3 pos,
												int32_t lifetime_and_delay[2]);
t_3d_object					*place_procedural_temp_object(t_doom3d *app,
												t_3d_object *model,
												const char *filenames[2],
												t_vec3 pos,
												int32_t lifetime_and_delay[2]);
void						get_mouse_world_position(t_doom3d *app,
													t_vec3 mouse_world_pos);
void						select_object(t_doom3d *app, t_3d_object *object);
void						deselect_object(t_doom3d *app, t_3d_object *obj);
void						editor_select_by_mouse(t_doom3d *app);
void						editor_deselect(t_doom3d *app);
void						editor_deselect_all(t_doom3d *app);
void						editor_init(t_doom3d *app, int32_t editor_level);
t_3d_object					*place_path_object(t_doom3d *app);
void						path_objects_set_neighbour(t_doom3d *app,
														t_3d_object *obj);
void						path_node_init(t_3d_object *path_obj);
void						path_draw_connections(t_render_work *work);
void						path_delete_connection(t_path_node *path_obj,
													t_path_node *delete);
void						delete_path_object_connections(t_path_node *node);
void						patrol_path_link_node(t_3d_object *node_obj,
								t_3d_object *obj, int slot);
void						editor_pos_camera_front(t_doom3d *app,
								t_vec3 result);
void						patrol_path_highlight(t_render_work *work);
void						trigger_update_key_id(t_doom3d *app,
								t_3d_object *key);
void						draw_aabb(t_doom3d *app, t_sub_framebuffer *buffers,
										t_box3d *aabb, uint32_t color);
void						editor_duplicate_selected_objects(t_doom3d *app);
char						*get_object_normal_map_filename(t_scene *scene,
								t_3d_object *obj);
char						*get_object_texture_filename(t_scene *scene,
								t_3d_object *obj);
uint32_t					get_light_emit_color(t_3d_object *light_obj);
t_shading_opts				get_light_shading(t_light_type
								light_type);
t_3d_object					*editor_place_light_object(t_doom3d *app,
								t_light_type light_type);
t_3d_object					*editor_place_trigger_object(t_doom3d *app,
								t_trigger_type type);
t_3d_object					*editor_place_default_object(t_doom3d *app,
								void *data);
t_3d_object					*editor_place_npc_object(t_doom3d *app,
								t_npc_type type);
t_3d_object					*place_window_wall_prefab(t_doom3d *app);
t_3d_object					*place_lava_plane_prefab(t_doom3d *app);

/*
** Level
*/

void						read_level_list(t_doom3d *app);

/*
** Menus
*/

t_button_group				*button_menu_create(t_doom3d *app,
								t_button_menu_params menu_params);
t_button_group				*button_menu_create_shaded(t_doom3d *app,
								t_button_menu_params menu_params);
void						main_menu_create(t_doom3d *app);
void						editor3d_menu_create(t_doom3d *app);
void						editor_popup_menu_create(t_doom3d *app,
								t_editor_menu_index new_menu,
								t_vec2 pos);
void						pause_menu_create(t_doom3d *app);
void						settings_menu_create(t_doom3d *app);
void						active_scene_menus_create(t_doom3d *app);
void						scene_menus_destroy(t_scene *scene);
void						editor_popup_menu_set(t_doom3d *app, t_vec2 pos,
								t_button_menu_params params);
t_surface					*menu_button_down_surface(const char *option,
								TTF_Font *font);
t_surface					*menu_button_surface(const char *option,
								TTF_Font *font);
t_surface					*menu_button_down_surface_shaded(const char *option,
								TTF_Font *font);
t_surface					*menu_button_surface_shaded(const char *option,
								TTF_Font *font);

/*
** Button clicks
*/

void						on_delete_menu_button_click(t_button *self,
								void *params);
void						on_editor_save_button_click(t_doom3d *app);
void						on_editor_exit_button_click(t_doom3d *app);
void						on_objects_menu_button_click(t_button *self,
								void *params);
void						on_textures_menu_button_click(t_button *self,
								void *params);
void						on_normmaps_menu_button_click(t_button *self,
								void *params);
void						on_npc_menu_button_click(t_button *self,
								void *params);
void						on_prefab_menu_button_click(t_button *self,
								void *params);
void						on_trigger_menu_button_click(t_button *self,
								void *params);
void						on_light_menu_button_click(t_button *self,
								void *params);
void						on_editor_menu_button_click(t_button *self,
								void *params);
void						on_new_level_menu_button_click(t_button *self,
								void *params);
void						on_guide_menu_button_click(t_button *self,
								void *params);

/*
** Utils
*/

void						resize_dependent_recreate(t_doom3d *app);
void						render_debug_info(t_doom3d *app);
void						capture_fps(t_doom3d *app);
uint64_t					performance_counter_start(void);
void						performance_counter_end(uint64_t start_time,
								char *task_name, float delta_limit);
void						notify_user(t_doom3d *app,
								t_notification notification);
void						update_notifications(t_doom3d *app);
void						delete_notifications(t_doom3d *app);
void						placement_notification(t_doom3d *app, char *txt);
uint32_t					arr_sum(uint32_t *arr, uint32_t length);

/*
** Triggers
*/

t_3d_object					*place_player_end(t_doom3d *app);
t_3d_object					*place_player_start(t_doom3d *app);
t_3d_object					*place_drop_shotgun(t_doom3d *app);
t_3d_object					*place_drop_pistol(t_doom3d *app);
t_3d_object					*place_drop_rpg(t_doom3d *app);
t_3d_object					*place_drop_jetpack(t_doom3d *app);
t_3d_object					*place_drop_medkit(t_doom3d *app);
t_3d_object					*place_elevator_switch(t_doom3d *app);
t_3d_object					*place_elevator_switch_timer(t_doom3d *app);
t_3d_object					*place_drop_key(t_doom3d *app);
t_3d_object					*place_hurt_box(t_doom3d *app);
t_3d_object					*place_jukebox(t_doom3d *app);
void						trigger_activate(t_doom3d *app, t_3d_object *obj);
void						trigger_link_object_to_npc(t_3d_object *trigger,
														t_3d_object *target);
void						trigger_timer_start(t_doom3d *app,
												t_3d_object *obj);
void						trigger_timer_update(t_doom3d *app);
void						get_trigger_action_text(t_trigger_type type,
													char *action_text);

/*
** Player animations
*/

void						set_player_animation(t_doom3d *app,
											uint32_t animation_id);
void						player_animations_init(t_doom3d *app);
void						player_animation_update(t_doom3d *app);
void						set_player_shoot_frame(t_doom3d *app);
void						set_player_reload_frame(t_doom3d *app);
void						set_player_default_frame(t_doom3d *app);
t_surface					*get_animation_source(t_doom3d *app);
t_player_anim_state			player_animation_state(t_doom3d *app);

/*
** Player HUD
*/

void						player_vitals_render(t_doom3d *app);

/*
** Sounds
*/

void						mp_init(t_doom3d *app);
t_mp						mix_chan_swap(t_doom3d *app, int channels);
t_mp						mix_init(t_doom3d *app, int channels);
t_track						*read_sound(char *file, t_doom3d *app);
void						mp_close(t_doom3d *app);
void						mp_au_mix(void *para, Uint8 *stream, int len);
t_sound						*s_ini(char loop, char priority, char type,
									float vol);
float						distance_vol(float max, float dist, float mdist);
float						sound_mag(t_vec3 v1, t_vec3 v2);
void						mp_typec(t_doom3d *app, char type, char sound,
									char state);
void						mp_print(t_mp *mp);
void						mp_reorder(t_sound **start, t_sound *new,
										t_sound *prev);
void						mp_music_init(t_doom3d *app);
void						mp_effect_init(t_doom3d *app);

#endif
