/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/21 15:26:27 by ohakola          ###   ########.fr       */
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
# define CLEAR_COLOR 0x700000FF
# define PLAYER_SPEED 6.0
# define PLAYER_ROTATION_SPEED 0.2
# define NEAR_CLIP_DIST 10
# define FAR_CLIP_DIST 100000
# define MAX_NUM_OBJECTS 16384
# define MAX_ASSETS 256
# define TEMP_OBJECT_EXPIRE_SEC 100

# define X_DIR 1
# define Y_DIR -1
# define Z_DIR 1

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
	scene_id_editor2d,
}							t_scene_id;

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
	t_bool					is_moving;
	t_bool					is_rotating;
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
}							t_player;

/*
** Save map data as .obj files & .txt files linking to textures.
** e.g: assets/map_data/level1_dir
**		assets/map_data/level1.data = t_map_file binary data
**		assets/map_data/level1_dir/object_key1.obj
**		assets/map_data/level1_dir/object_key2.obj
**		assets/map_data/level1_dir/object_key1_texture.txt text file containing
** path of the texture file.
**		assets/map_data/level1_dir/object_key2_texture.txt text file containing
** path of the texture file.
*/

typedef struct				s_map_file
{
	char					header[4];
	uint32_t				object_ids[MAX_ASSETS];
	uint32_t				num_objects;
}							t_map_file;

typedef struct				s_asset_files
{
	char					*texture_files[MAX_ASSETS];
	char					*normal_map_files[MAX_ASSETS];
	char					*model_files[MAX_ASSETS];
	uint32_t				asset_keys[MAX_ASSETS];
	uint32_t				num_assets;
}							t_asset_files;

typedef struct				s_scene
{
	t_3d_object				*objects[MAX_NUM_OBJECTS];
	uint32_t				num_objects;
	t_kd_tree				*triangle_tree;
	t_triangle				**triangle_ref;
	uint32_t				num_triangles;
	t_camera				*main_camera;
	t_triangle				*screen_triangles;
	t_button_group			*menus[8];
	uint32_t				num_menus;
	t_bool					is_paused;
	t_scene_id				scene_id;
	t_hash_table			*textures;
	t_hash_table			*normal_maps;
	t_hash_table			*models;
	t_asset_files			asset_files;
	t_surface				*skybox_textures[6];
	t_3d_object				*skybox[6];
}							t_scene;

typedef struct				s_doom3d
{
	t_bool					is_running;
	t_bool					is_debug;
	t_bool					is_loading;
	t_bool					is_normal_map;
	t_bool					is_first_render;
	t_bool					is_saving;
	t_info					info;
	t_window				*window;
	t_scene_id				next_scene_id;
	t_scene					*active_scene;
	t_player				player;
	t_mouse					mouse;
	t_keyboard				keyboard;
	t_thread_pool			*thread_pool;
	float					unit_size;
	t_bool					is_minimap_largened;
	int32_t					triangles_in_view;
	char					editor_filename[128];
}							t_doom3d;

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
void						player_scroll_editor(t_doom3d *app, float speed);

/*
** Events
*/
void						events_handle(t_doom3d *app);
void						mouse_state_handle(t_doom3d *app);
void						player_shoot(t_doom3d *app,
								uint32_t curr_time);
void						keyboard_state_handle(t_doom3d *app);
void						general_input_events_handle(t_doom3d *app,
								SDL_Event event);

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
void						menu_render(t_button_group *menu, t_vec2 pos);

/*
** Scene
*/
void						scene_assets_load(t_scene *scene);
void						active_scene_content_set(t_doom3d *app);
t_scene						*scene_new(t_scene_id scene_id);
void						scene_destroy(t_scene *scene);
void						scene_next_select(t_doom3d *app);
void						scene_debug(t_scene *scene);
void						scene_map_init(t_scene *scene);
void						scene_camera_destroy(t_scene *scene);
void						scene_objects_destroy(t_scene *scene);
void						scene_skybox_destroy(t_scene *scene);
void						scene_models_destroy(t_scene *scene);
void						scene_textures_destroy(t_scene *scene);
void						scene_normal_maps_destroy(t_scene *scene);

/*
** Editor
*/
uint32_t					random_uuid(void);


/*
** Menus
*/
t_button_group				*button_menu_create(t_doom3d *app,
								const char **options, int32_t num_buttons,
								void (*on_click)(t_button *, void *));
void						main_menu_create(t_doom3d *app);
void						editor3d_menu_create(t_doom3d *app);
void						editor2d_menu_create(t_doom3d *app);
void						pause_menu_create(t_doom3d *app);
void						settings_menu_create(t_doom3d *app);
void						active_scene_menu_recreate(t_doom3d *app);
void						scene_menus_destroy(t_scene *scene);

/*
** Debug
*/
void						doom3d_debug_info_render(t_doom3d *app);
void						doom3d_debug_info_capture(t_doom3d *app);
uint64_t					doom3d_performance_counter_start(void);
void						doom3d_performance_counter_end(uint64_t start_time,
								char *task_name, float delta_limit);

#endif
