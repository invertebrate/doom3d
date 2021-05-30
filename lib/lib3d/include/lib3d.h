/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 18:54:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB3D_H
# define LIB3D_H

# include <stdlib.h>
# include <float.h>
# include "libft.h"
# include "libgmatrix.h"

# define L3D_EPSILON 0.0000001
# define L3D_SINGLE_SIDED 1
# define L3D_MAX_KD_TREE_DEPTH 10

# define L3D_MIN_KD_NODE_NUM_TRIANGLES 4
# define L3D_TRI_VEC_INITIAL_CAPACITY 30

/*
** refers to screen buffer's split in x dir and y dir
*/

# define L3D_BUFFER_SPLIT_SIZE_X 4
# define L3D_BUFFER_SPLIT_SIZE_Y 2

# define L3D_MAX_OBJ_TRIANGLES 16384
# define L3D_MAX_OBJ_VERTICES 16384

# define L3D_DEFAULT_COLOR 0xff00ffff
# define L3D_DEFAULT_COLOR_TRANSPARENT 0xff00ff64

# define L3D_COLOR_WHITE 0xffffffff
# define L3D_COLOR_PINK 0xff00ffff
# define L3D_COLOR_RED 0xff0000ff
# define L3D_COLOR_GREEN 0x00ff00ff
# define L3D_COLOR_BLUE 0x0000ffff
# define L3D_COLOR_YELLOW 0xffff00ff
# define L3D_COLOR_EXPLOSION 0xffa255ff
# define L3D_COLOR_LIGHT_YELLOW 0xffff80ff
# define L3D_COLOR_CYAN 0x00ffffff
# define L3D_COLOR_WHITE_TRANSPARENT 0xffffff64
# define L3D_COLOR_PINK_TRANSPARENT 0xff00ff64
# define L3D_COLOR_RED_TRANSPARENT 0xff000064
# define L3D_COLOR_GREEN_TRANSPARENT 0x00ff0064
# define L3D_COLOR_BLUE_TRANSPARENT 0x0000ff64
# define L3D_COLOR_YELLOW_TRANSPARENT 0xffff0064
# define L3D_COLOR_LIGHT_YELLOW_TRANSPARENT 0xffff8064
# define L3D_COLOR_CYAN_TRANSPARENT 0x00ffff64

# define L3D_MAX_LIGHTS 32

/*
** OBJ file temporary structs. They are used in transfering obj data to final
** t_3d_obj form. These structs are easier to use in obj reading, but don't
** really fit to the rest of the 3d stuff.
*/

typedef struct s_obj
{
	t_vec3			*v;
	uint32_t		num_vertices;
	t_vec2			*vt;
	uint32_t		num_v_text_coords;
	t_vec3			*vn;
	uint32_t		num_v_normals;
	uint32_t		*triangles;
	uint32_t		num_triangles;
}							t_obj;

/*
** Basic vertex struct with position, color and texture coordinates.
*/

typedef struct s_vertex
{
	t_vec4			pos;
	uint32_t		color;
}							t_vertex;

/*
** Ray with direction and origin. Dir_inv is precalculated for faster
** bounding box intersection calculations.
*/

typedef struct s_ray
{
	t_vec3			dir;
	t_vec3			origin;
	t_vec3			dir_inv;
}							t_ray;

/*
** Structure representing a circular orthogonal cone in 3d space.
*/

typedef struct s_cone
{
	t_vec3			apex;
	t_vec3			dir;
	float			height;
	float			radius;
}							t_cone;

/*
** Structure representing a directed sphere in 3D space. Height is an optional
** parameter to adjust the vertical scale. 
*/

typedef struct s_sphere
{
	t_vec3			pos;
	t_vec3			up;
	t_vec3			forward;
	float			radius;
	float			height;

}							t_sphere;

/*
** Structure representing a directed cylinder in 3D space.
*/

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			up;
	t_vec3			forward;
	float			radius;
	float			height;

}							t_cylinder;

/*
** Enums defining how to shade (in rasterization) the 3d object
** E.g. e_shading_transparent = use alpha blending
** E.g. e_shading_zero_alpha = if alpha == 0, render nothing on that pixel
*/

typedef enum e_shading_opts
{
	e_shading_normal_map = 1 << 1,
	e_shading_zero_alpha = 1 << 2,
	e_shading_ignore_zpass = 1 << 3,
	e_shading_select = 1 << 4,
	e_shading_invisible = 1 << 5,
	e_shading_red = 1 << 6,
	e_shading_green = 1 << 7,
	e_shading_blue = 1 << 8,
	e_shading_yellow = 1 << 9,
	e_shading_cyan = 1 << 10,
	e_shading_transparent = 1 << 11,
	e_shading_uv_repeat = 1 << 12,
	e_shading_light = 1 << 13,
	e_shading_temp_invisible = 1 << 14,
	e_shading_white = 1 << 15,
	e_shading_luminous = 1 << 20,
	e_shading_standard = 1 << 17,
	e_shading_lit = 1 << 18,
	e_shading_emitter = 1 << 19,
	e_shading_dont_cull = 1 << 21,
	e_shading_blue_highlight = 1 << 22,
}							t_shading_opts;

/*
** Surface describes width and height of an image and contains the pixel data
** of the image
*/

typedef struct s_surface
{
	uint32_t		*pixels;
	uint32_t		w;
	uint32_t		h;
	const char		*filename;
}							t_surface;

typedef struct s_flashlight
{
	t_cone					cone;
	uint32_t				light_color;
	float					intensity;
	t_bool					active;
	t_bool					enabled;
}							t_flashlight;

/*
** Light source defines how light is rendered in rasterization
** if it's been set for material of the object
*/

typedef struct s_light_source
{
	t_vec3		pos;
	float		radius;
	float		intensity;
	uint32_t	color;
}							t_light_source;

/*
** Material contains object texture and normal map information and other
** rendering related parameters such as shading opts and light sources
*/

typedef struct s_material
{
	t_surface		*texture;
	t_surface		*normal_map;
	t_shading_opts	shading_opts;
	t_light_source	light_sources[L3D_MAX_LIGHTS];
	t_flashlight	*flashlight;
	uint32_t		num_lights;
}							t_material;

typedef struct s_3d_object	t_3d_object;

/*
** Triangle contains pointers to vertices (which get transformed over time)
** Center and normal should be updated if vertices are transformed.
*/

typedef struct s_triangle
{
	t_bool			is_single_sided;
	t_bool			clipped;
	t_3d_object		*parent;
	t_material		*material;
	t_vertex		*vtc[3];
	uint32_t		vtc_indices[3];
	t_vec2			points_2d[3];
	t_vec2			uvs[3];
	t_vec3			normals[3];
	t_vec3			center;
	t_vec3			normal;
	t_vec3			ab;
	t_vec3			ac;
	t_vec3			tangent;
	t_vec3			bitangent;
	t_vec3			normalized_normal;
	t_vec3			vtc_zvalue;
}							t_triangle;

/*
** Sub framebuffer struct defining a portion of a main framebuffer used
** in parallel rendering
*/

typedef struct s_sub_framebuffer
{
	uint32_t		*buffer;
	float			*zbuffer;
	int32_t			width;
	int32_t			height;
	int32_t			x_start;
	int32_t			y_start;
	int32_t			parent_width;
	int32_t			parent_height;
	float			x_offset;
	float			y_offset;
}							t_sub_framebuffer;

/*
** A main framebuffer containing sub parts (sub frame buffers) and the main
** pixels to which the sub parts are then copied by threads
*/

typedef struct s_framebuffer
{
	uint32_t			*buffer;
	int32_t				width;
	int32_t				height;
	t_sub_framebuffer	**sub_buffers;
	int32_t				num_x;
	int32_t				num_y;
}							t_framebuffer;

/*
** Ray hit is saved to this hit record struct. Add params if needed.
** For example material information could be saved here.
*/

typedef struct s_hit
{
	float			t;
	float			u;
	float			v;
	t_vec3			normal;
	t_vec3			hit_point;
	t_triangle		*triangle;
}							t_hit;

typedef t_list				t_hits;

/*
** Bounding box AABB. Minimum and maximum coordinates are used in
** bounding box ray intersection calculations.
** center and size are useful in kd_tree / bvh structs.
*/

typedef struct s_box3d
{
	t_vec3			center;
	t_vec3			size;
	float			xyz_min[3];
	float			xyz_max[3];
	t_bool			is_collider;
}							t_box3d;

/*
**	Describes an infinite plane in 3D. Origin is any point that is on the plane
*/

typedef struct s_plane
{
	t_vec3		origin;
	t_vec3		normal;
	float		d;
}							t_plane;

/*
** Final 3d object struct to which obj file is transformed.
** This is the main struct to hold 3d object data.
*/

struct s_3d_object
{
	uint32_t		id;
	uint32_t		type;
	void			*params;
	uint32_t		params_size;
	uint32_t		params_type;
	t_vertex		**vertices;
	int32_t			num_vertices;
	t_triangle		*triangles;
	int32_t			num_triangles;
	t_material		*material;
	t_mat4			rotation;
	t_mat4			scale;
	t_vec3			position;
	t_box3d			aabb;
};

/*
** Utility enum for x y z axes.
*/

typedef enum e_axis
{
	l3d_axis_x,
	l3d_axis_y,
	l3d_axis_z,
	l3d_axis_none,
}							t_axis;

/*
** Triangle vector struct holding pointers to triangles. Kd tree uses this, but
** can be used in isolation as well. Triangles can be pushed to an existing
** triangle vector.
*/

typedef struct s_tri_vec
{
	t_triangle		**triangles;
	uint32_t		size;
	uint32_t		capacity;
}							t_tri_vec;

typedef struct s_kd_node	t_kd_node;

/*
** Kd node is a single node in kd tree containing triangle information and
** bounding box information.
*/

struct s_kd_node
{
	uint32_t		uuid;
	t_box3d			bounding_box;
	t_axis			axis;
	t_tri_vec		*triangles;
	t_kd_node		*left;
	t_kd_node		*right;
	int32_t			depth;
};

/*
** BVH (kd tree) for fast ray intersection calculations (or collisions).
** It's used to partition triangle data into a fast searchable format.
*/

typedef struct s_kd_tree
{
	uint32_t		num_nodes;
	t_kd_node		*root;
}							t_kd_tree;

/*
** Temporary object is rendered with a delay and exists only during its
** lifetime
*/

typedef struct s_temp_object
{
	int32_t					lifetime;
	int32_t					delay;
	t_3d_object				*obj;
}							t_temp_object;

/*
** A linked list of temp objects
*/

typedef t_list				t_temp_objects;

/*
** Kd tree
*/

void						l3d_kd_tree_create_or_update(t_kd_tree **tree,
								t_triangle **triangles, uint32_t num_triangles);
t_kd_tree					*l3d_kd_tree_create(t_triangle **triangles,
								uint32_t num_triangles);
void						l3d_kd_tree_destroy(t_kd_tree *tree);
void						l3d_kd_tree_print(t_kd_tree *tree);

/*
** Ray
*/

t_bool						l3d_triangle_ray_hit(t_triangle *triangle,
								t_ray *ray, t_hits **hits);
t_bool						l3d_bounding_box_ray_hit(t_box3d *box,
								t_ray *ray, t_hits **hits, t_bool is_recorded);
void						l3d_ray_set(t_vec3 dir, t_vec3 origin, t_ray *ray);
void						l3d_triangle_hit_record_set(float afuvt[5],
								t_ray *ray,
								t_triangle *triangle, t_hits **hits);
void						l3d_bounding_box_hit_record_set(float t[8],
								t_ray *ray, t_hits **hits);
t_bool						l3d_plane_ray_hit(t_plane *plane, t_ray *ray,
								t_vec3 hit_point);
void						l3d_delete_hits(t_hits **hits);
void						l3d_get_closest_triangle_hit(t_hits *hits,
								t_hit **closest,
								uint32_t ignore_id);
void						l3d_get_closest_facing_triangle_hit(t_hits *hits,
								t_hit **closest,
								t_vec3 dir,
								uint32_t ignore_id);
void						l3d_get_closest_triangle_hit_at_range(t_hits *hits,
								t_hit **closest,
								uint32_t ignore_id, float range);
void						l3d_get_closest_hit(t_hits *hits,
								t_hit **closest);
t_bool						l3d_kd_tree_ray_hits(t_kd_tree *triangle_tree,
								t_vec3 origin, t_vec3 dir, t_hits **hits);
void						l3d_cast_rays_sphere(t_ray *rays,
								uint32_t *ray_counts, t_sphere *sphere);
void						l3d_cast_rays_cylinder(t_ray *rays,
								uint32_t *ray_counts, t_cylinder *cylinder);

/*
** Triangle vector
*/

void						l3d_triangle_vec_push(t_tri_vec *vector,
								t_triangle *triangle);
t_tri_vec					*l3d_triangle_vec_empty(void);
t_tri_vec					*l3d_triangle_vec(t_triangle **triangles,
								uint32_t num_triangles);
void						l3d_triangle_vec_delete(t_tri_vec *vector);
t_tri_vec					*l3d_triangle_vec_with_capacity(uint32_t capacity);

/*
** Triangles
*/

void						l3d_triangle_set(t_triangle *triangle,
								t_vertex *vtc[3], t_3d_object *obj);
void						l3d_triangle_update(t_triangle *triangle);
void						l3d_triangles_midpoint(t_triangle **triangles,
								uint32_t num_triangles, t_vec3 res);
void						l3d_triangle_vec_midpoint(t_tri_vec *triangles,
								t_vec3 res);
void						l3d_triangle_centroid_update(t_triangle *triangle);
void						l3d_triangle_normal_update(t_triangle *triangle);
void						l3d_triangle_tangent_update(t_triangle *triangle);
void						l3d_triangle_destroy(t_triangle *triangle,
								t_bool with_vertices);
t_triangle					*l3d_triangle_clone(t_triangle *src,
								t_bool new_vertices);
void						*l3d_triangle_copy(t_triangle *dst,
								t_triangle *src);
void						triangle_sort_by_morton_code(t_tri_vec *triangles,
								t_thread_pool *pool, t_box3d *world_box);
void						triangle_sort_by_depth(t_tri_vec *triangles,
								t_thread_pool *pool, t_box3d *world_box);
void						normalize_by_world_box(t_vec3 position,
								t_box3d *world_box);
void						triangle_sort_free(t_triangle **tmp,
								uint32_t *keys,
								uint32_t *indices);
uint32_t					get_padded_size(uint32_t size);
void						reorder_sorted_triangles(t_tri_vec *triangles,
								t_triangle **tmp,
								uint32_t *key_vals[2]);

/*
**	Triangle clipping
*/

int							l3d_clip_triangle(t_triangle *triangle,
								t_plane *plane,
								t_triangle *result_triangles[2]);
void						l3d_init_clipped_triangles(t_triangle
								*clipped_tris[2]);
int							l3d_triangle_test_clip(t_triangle *triangle,
								t_plane *plane,
								int *point_indices);

/*
** Bounding box
*/

t_box3d						l3d_triangle_bounding_box(t_triangle *triangle);
t_axis						l3d_bounding_box_longest_axis(t_box3d bounding_box);
void						l3d_bounding_box_set(t_tri_vec *triangles,
								t_box3d *res);
void						l3d_object_aabb_update(t_3d_object *obj);
t_bool						l3d_aabb_collides(t_box3d *left, t_box3d *right);
t_bool						l3d_point_inside_aabb(t_box3d *aabb, t_vec3 point);
t_hit						*l3d_get_aabb_hit_record(t_box3d *origin,
								t_box3d *target);

/*
** 3d objects
*/

void						l3d_3d_object_rotate_matrix(t_3d_object *object,
								t_mat4 rotation);
void						l3d_3d_object_transform(t_3d_object *obj,
								t_mat4 transform);
void						l3d_3d_object_translate(t_3d_object *object,
								float x, float y, float z);
void						l3d_3d_object_scale(t_3d_object *object,
								float x, float y, float z);
void						l3d_3d_object_scale_with_uvs(t_3d_object *object,
								float scale_amount);
void						l3d_3d_object_rotate(t_3d_object *object,
								float x, float y, float z);
t_3d_object					*l3d_3d_object_create(uint32_t num_vertices,
								uint32_t num_triangles);
void						l3d_3d_object_destroy(t_3d_object *object);
void						l3d_3d_object_set_vertex(t_vertex *vertex,
								t_vec3 pos);
t_3d_object					*l3d_3d_object_copy(t_3d_object *src);
void						l3d_object_set_shading_opts(t_3d_object *obj,
								t_shading_opts opts);
t_3d_object					*l3d_3d_object_shallow_copy(t_3d_object *src);
void						l3d_3d_object_triangle_copy_and_set(
								t_3d_object *dst,
								t_3d_object *src);
void						l3d_3d_object_set_params(t_3d_object *object,
								void *params, uint32_t params_size,
								uint32_t params_type);
void						l3d_3d_object_add_light_source(t_3d_object *object,
								t_vec3 light_pos,
								float radius_intensity[2],
								uint32_t emit_color);
float						*point_inside_cone(t_cone *cone, t_vec3 point,
								float *vars);
void						get_world_pos_persp_corr(t_triangle *triangle,
								t_vec3 baryc,
								t_vec3 world_pos);

/*
** OBJ reading
*/

t_3d_object					*l3d_read_obj(const char *filename,
								t_surface *texture,
								t_surface *normal_map);

/*
** Math utils (could be moved somewhere else...)
*/

float						l3d_fmax(float n1, float n2);
float						l3d_fmin(float n1, float n2);
double						l3d_rand_d(void);
uint32_t					l3d_random_uuid(void);

/*
**	Triangle rasterization
*/

void						l3d_triangle_raster(t_sub_framebuffer *buffers,
								t_triangle *triangle);
void						l3d_triangle_raster_transparent(t_sub_framebuffer
								*buffers,
								t_triangle *triangle);
void						l3d_calculate_baryc(
								t_vec2 *triangle_points_2d,
								t_vec2 point,
								float *barycoords);
void						l3d_interpolate_uv(t_triangle *triangle,
								float *barycoords,
								t_vec2 point_uv);
uint32_t					l3d_sample_texture(t_surface *material,
								t_vec2 uv_point);
void						l3d_order_corners_y(t_vec2 *ordered_corners,
								t_vec2 *points_2d);
float						l3d_z_val(float baryc[3], t_triangle *triangle);
uint32_t					l3d_pixel_depth_shaded(uint32_t pixel, float z_val);
uint32_t					l3d_pixel_normal_shaded(uint32_t pixel,
								t_triangle *triangle, t_vec2 uv);
uint32_t					l3d_pixel_selection_shaded(uint32_t pixel);
void						l3d_clamp_uv(t_vec2 uv);
void						l3d_uv_repeat(t_vec2 uv);
void						l3d_clamp_or_repeat_uv(t_triangle *triangle,
								t_vec2 uv);
void						l3d_raster_draw_pixel(t_sub_framebuffer *buffers,
								int32_t xy[2],
								t_triangle *triangle);
void						l3d_raster_draw_pixel_transparent(t_sub_framebuffer
								*buffers,
								int32_t xy[2],
								t_triangle *triangle);
uint32_t					l3d_pixel_light_shaded(t_triangle *triangle,
								t_vec3 baryc, uint32_t pixel);
uint32_t					l3d_blend_pixel(t_sub_framebuffer *buffers,
								int32_t offset_xy[2], uint32_t pixel);

/*
** Plot pixel
*/

void						l3d_pixel_plot(uint32_t *buffer,
								uint32_t dimensions_wh[2],
								int32_t xy[2],
								uint32_t color);
uint32_t					l3d_pixel_get(uint32_t *buffer,
								uint32_t dimensions_wh[2],
								int32_t xy[2]);
float						l3d_pixel_get_float(float *buffer,
								uint32_t dimensions_wh[2], int32_t xy[2]);
void						l3d_pixel_plot_float(float *buffer,
								uint32_t dimensions_wh[2], int32_t xy[2],
								float value);
void						calculate_luminosity(uint32_t *pixel,
								uint32_t *light,
								uint32_t darkness);
void						l3d_write_z_val(
								t_sub_framebuffer *buffers,
								t_triangle *triangle,
								int32_t offset_xy[2], float z_val);

/*
** Line draw
*/

void						l3d_line_draw(uint32_t *buffer,
								uint32_t dimensions_wh[2], int32_t edge[2][2],
								uint32_t color);
void						l3d_triangle_2d_draw(uint32_t *buffer,
								uint32_t dimensions_wh[2],
								t_vec2 corners[3], uint32_t color);
void						l3d_edge_aabb_intersections(t_vec2 aabb[2],
								t_vec2 edge[2], int32_t is_intersect[4],
								t_vec2 intersects[4]);
t_bool						l3d_clamp_edge_within_aabb(t_vec2 aabb[2],
								t_vec2 edge[2], int32_t is_intersect[4],
								t_vec2 intersects[4]);

/*
** Bmp reading
*/

void						l3d_read_bmp_image_32bit_rgba(const char *filename,
								uint32_t **pixels_out, uint32_t *width,
								uint32_t *height);
t_surface					*l3d_read_bmp_32bit_rgba_surface(
								const char *filename);

/*
** Buffer image copying / placing
*/

void						l3d_background_place(t_surface *frame,
								t_surface *image,
								float blend_ratio);
void						l3d_image_place(t_surface *frame,
								t_surface *image, int32_t pos_xy[2],
								float blend_ratio);
t_surface					*l3d_image_scaled(t_surface *image,
								int32_t dest_x, int32_t dest_y);

/*
** Color utils
*/

uint32_t					l3d_rgba_to_u32(uint32_t rgba[4]);
uint32_t					l3d_color_blend_u32(uint32_t color1,
								uint32_t color2, float ratio);
uint32_t					l3d_color_alpha_blend_u32(uint32_t color1,
								uint32_t color2);
void						l3d_u32_to_rgba(uint32_t color, uint32_t rgba[4]);
uint32_t					l3d_triangle_normal_color(t_triangle *triangle);

/*
** Framebuffer utils
*/

t_framebuffer				*l3d_framebuffer_create(int32_t width,
								int32_t height);
void						l3d_framebuffer_destroy(t_framebuffer *framebuffer);
void						l3d_framebuffer_recreate(
								t_framebuffer **framebuffer,
								int32_t width, int32_t height);
void						l3d_buffer_float_clear(float *buffer,
								uint32_t size, float clear_value);
void						l3d_buffer_uint32_clear(uint32_t *buffer,
								uint32_t size, uint32_t clear_value);

/*
** Procedural gen
*/

void						l3d_skybox_create(t_3d_object *skybox[6],
								t_surface *skybox_textures[6],
								float unit_size);
t_3d_object					*l3d_plane_create(t_surface	*texture,
								t_surface *normal_map);
t_3d_object					*l3d_object_instantiate(t_3d_object *model,
								float unit_size);
void						l3d_temp_objects_add(t_temp_objects **temp_objects,
								t_3d_object *object,
								int32_t lifetime_and_delay[2]);
void						l3d_temp_objects_destroy(
								t_temp_objects **temp_objects);
void						l3d_temp_objects_destroy_if_expired(
								t_temp_objects **temp_objects);
void						l3d_temp_objects_update_time(
								t_temp_objects **temp_objects,
								uint32_t delta_time);

#endif
