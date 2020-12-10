/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3d_internals.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:53:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB3D_INTERNALS_H
# define LIB3D_INTERNALS_H

# include "lib3d.h"

/*
** Make sure file header data alignment is correct
*/

# pragma pack(push)
# pragma pack(1)

/*
** Don't use image size which can be zero for uncompressed bmps
** https://elcharolin.wordpress.com/2018/11/28/read-and-write-bmp-files-in-c-c/
*/

typedef struct				s_bmp_file_header
{
	uint16_t	file_type;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	data_offset;
	uint32_t	info_size;
	int32_t		width;
	int32_t		height;
	uint16_t	color_planes;
	uint16_t	bits_per_pixel;
	uint32_t	compression_type;
	uint32_t	image_size;
	int32_t		pixels_per_meter_x;
	int32_t		pixels_per_meter_y;
	uint32_t	number_of_bit_map_colors;
	uint32_t	number_of_important_colors;
}							t_bmp_file_header;

# pragma pack(pop)

typedef struct				s_image_data
{
	unsigned char	*pixels;
	uint32_t		width;
	uint32_t		height;
	uint32_t		bytes_per_pixel;
}							t_image_data;

typedef struct				s_raster_data
{
	float	x1;
	float	x2;
	float	x3;
	float	y1;
	float	y2;
	float	y3;
	float	slope_ab;
	float	slope_bc;
	float	slope_ac;
}							t_raster_data;

/*
** OBJ reading
*/

void						l3d_read_obj_triangle_line(char **str,
								uint32_t *triangle);
void						l3d_read_obj_vec2_line(char **str, t_vec3 res);
void						l3d_read_obj_vec3_line(char **str, t_vec3 res);
t_bool						l3d_is_valid_obj(t_obj *obj);
void						l3d_obj_str_parse(char *str, t_obj *obj);
void						l3d_obj_content_allocate(t_obj *obj);
void						l3d_obj_content_free(t_obj *obj);

/*
** Kd Tree
*/

void						l3d_kd_tree_split_triangles(t_tri_vec *triangles,
								uint32_t axis, t_tri_vec *left_tris,
								t_tri_vec *right_tris);
t_kd_node					*l3d_kd_node_create(t_tri_vec *triangles);
void						l3d_kd_node_destroy(t_kd_node *root);

/*
** Triangle clipping
*/
t_bool						l3d_interpolate_clipped_uv(t_triangle *triangle,
								int32_t *limits, t_vec3 hit, t_vec2 result);
int32_t						l3d_triangle_clipping_case(t_triangle *triangle,
								t_plane *near, int32_t *point_indices);
t_bool						create_one_clipped_triangle(t_triangle *triangle,
								t_plane *plane, int32_t *indices,
								t_triangle *result_tris);
t_bool						create_two_clipped_triangles(t_triangle *triangle,
								t_plane *plane, int32_t *indices,
								t_triangle *result_tris);

#endif
