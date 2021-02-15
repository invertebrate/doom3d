/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/15 22:00:02 by ohakola          ###   ########.fr       */
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
# define CONST_GRAVITY 1.06
/*
** // ToDo: Create toggleable settings
*/

typedef struct				s_settings
{
	t_bool					is_normal_map;
	t_bool					is_skybox;
	int32_t					width;
	int32_t					height;
}							t_settings;

/*
** Main struct, "The App".
*/

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
	uint64_t				current_tick;
	t_settings				settings;
	t_list					*notifications;
	t_projectile			projectile_data[NUM_PROJECTILES];
	t_weapon				weapons_data[NUM_WEAPONS];
	t_sprite_anim			animations[NUM_PLAYER_ANIMATIONS];
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
}							t_render_work;

void						doom3d_run(t_doom3d *app);

/*
** Player
*/
void						doom3d_player_update(t_doom3d *app);
void						player_init(t_doom3d *app, t_vec3 pos);
void						player_move(t_doom3d *app);
void						get_move_dir(t_doom3d *app,
								t_move dir_option, t_vec3 dir);
void						player_rotate_vertical(t_doom3d *app, float angle);
void						player_rotate_horizontal(t_doom3d *app,
								float angle);
void						player_apply_gravity(t_doom3d *app);
void						collision_limit_player(t_doom3d *app, t_vec3 add);
void						player_update_aabb(t_player *player);
void						editor_vertical_move(t_doom3d *app, float speed);
void						player_onhit(t_doom3d *app, int damage);
void						player_jump(t_doom3d *app);
void						player_crouch(t_doom3d *app, t_bool toggle);
void						player_shoot(t_doom3d *app,
								uint32_t curr_time);

/*
** Player items
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
** Projectiles
*/
void						projectile_data_init(t_doom3d *app);
t_projectile				projectile_data_rpg(t_doom3d *app);
void						projectile_update(t_doom3d *app, t_3d_object *obj);
void						projectile_explosion(t_doom3d *app, t_vec3 pos,
								t_projectile *projectile);
void						place_projectile_object_in_scene(t_doom3d *app,
							t_projectile *projectile, t_vec3 origin, t_vec3 rot);

/*
** Npcs
*/
void						npc_spawn(t_doom3d *app, t_vec3 pos, float angle,
								int type);
void						npc_update_state(t_doom3d *app, t_3d_object *npc_obj);
void						npc_execute_behavior(t_doom3d *app,
								t_3d_object *npc_obj);
void						npc_default(t_doom3d *app, t_npc *npc);
void						handle_npc_deletions(t_doom3d *app);
void						parse_npc_type(t_doom3d *app, t_npc *npc, int type);
void						npc_trigger_onhit(t_doom3d *app,
								t_3d_object *obj, int damage);
void						npc_get_dir_to_next_waypoint(t_doom3d *app, t_3d_object *obj);
void						npc_move_step_to_waypoint(t_doom3d *app, t_3d_object *obj);

/*
** Physics
*/

t_bool						obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj);
t_bool						player_is_grounded(t_doom3d *app);
void						forces_update_object(t_doom3d *app,
								t_3d_object *tested);
void						forces_update_player(t_doom3d *app);

/*
** Events
*/
void						doom3d_events_handle(t_doom3d *app);
void						mouse_state_handle(t_doom3d *app);
void						keyboard_state_handle(t_doom3d *app);
void						general_input_events_handle(t_doom3d *app,
								SDL_Event event);
void						handle_editor_selection(t_doom3d *app,
								SDL_Event event);
void						handle_editor_saving(t_doom3d *app,
								SDL_Event event);
t_bool						editor_popup_menu_open(t_doom3d *app);

/*
** 3D Animations
*/

void						npc_animation_3d_set(t_doom3d *app, t_3d_object *obj, t_npc *npc,
											t_anim_metadata *anim_data);
void						npc_animation_3d_init(t_doom3d *app, t_3d_object *obj);
void						update_app_ticks(t_doom3d *app);
uint32_t					anim_3d_frame_update(t_doom3d *app, t_animation_3d *animation);
void						anim_3d_clip_set(t_doom3d *app, t_3d_object *obj,
											t_animation_3d_type clip, uint32_t start_frame);
void						npc_anim_3d_position_update(t_3d_object *obj);

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
void						button_menu_render(t_button_group *menu,
								t_vec2 pos);
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
void						draw_enemy_direction(t_doom3d *app,
								t_sub_framebuffer *sub_buffer,
								t_3d_object *npc_object);
void						draw_npc_dirs(t_render_work *work);
void						notifications_render(t_doom3d *app, t_vec2 pos);
void						draw_triangle_tree_bounding_boxes(
								t_render_work *work);
void						draw_editor_placement_position(t_render_work *work);

/*
** Objects
*/
void						doom3d_update_objects(t_doom3d *app);
void						object_type_to_str(t_3d_object *obj, char *str);
t_3d_object					*find_one_object_by_type(t_doom3d *app,
								uint32_t object_type,
								uint32_t param_type);
void						path_objects_set_neighbors(t_doom3d *app);
t_3d_object					*find_object_by_id(t_doom3d *app, uint32_t id);

/*
** Scene
*/
void						scene_assets_load(t_scene *scene);
void						active_scene_content_set(t_doom3d *app);
void						active_scene_update_after_objects(t_scene *scene);
t_scene						*scene_new(t_scene_id scene_id);
void						scene_destroy(t_doom3d *app);
void						scene_next_select(t_doom3d *app);
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
t_3d_object					*place_temp_object(t_doom3d *app,
								const char *filenames[3],
								t_vec3 pos, int32_t lifetime_and_delay[2]);
t_3d_object					*place_procedural_temp_object(t_doom3d *app,
								t_3d_object *model,
								const char *filenames[2],
								t_vec3 pos, int32_t lifetime_and_delay[2]);
void						editor_select(t_doom3d *app);
void						editor_deselect_all(t_doom3d *app);
void						editor_deselect(t_doom3d *app);
void						after_editor_transform(t_doom3d *app,
								uint32_t *last_changed);
void    					editor_init(t_doom3d *app, int32_t editor_level);
void						place_path_object(t_doom3d *app);
void						path_objects_set_neighbour(t_doom3d *app, t_3d_object *obj);
void						path_node_init(t_3d_object *path_obj);
void						path_draw_connections(t_render_work *work);
void						path_delete_connection(t_path_node *path_obj,
													t_path_node *delete);
void						delete_path_object_connections(t_path_node *node);
void						patrol_path_link_node(t_3d_object *node_obj, t_3d_object *obj, int slot);
void						editor_place_position(t_doom3d *app ,
								t_vec3 result);
void						patrol_path_highlight(t_render_work *work);
void						draw_aabb(t_doom3d *app, t_sub_framebuffer *buffers,
										t_box3d *aabb, uint32_t color);

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
void						place_drop_jetpack(t_doom3d *app);
void						editor_objects_invisible_unhighlight(t_doom3d *app);
void						editor_objects_invisible_highlight(t_doom3d *app);

/*
** Player animations
*/
void						player_animations_init(t_doom3d *app);
void						doom3d_player_animation_update(t_doom3d *app);
void						set_player_shoot_frame(t_doom3d *app);
void						set_player_reload_frame(t_doom3d *app);
void						set_player_default_frame(t_doom3d *app);
t_surface					*get_animation_source(t_doom3d *app);

/*
** Player HUD
*/
void						player_vitals_render(t_doom3d *app);

#endif
