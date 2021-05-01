# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#              #
#    Updated: 2021/05/02 00:13:27 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = lib3d.a
LIBFT = ../libft
LIBGMATRIX = ../libgmatrix
DIR_SRC = ./
DIR_OBJ = temp
SOURCES = l3d_triangle.c \
			l3d_triangle_clone.c \
			l3d_triangle_update.c \
			l3d_triangle_vector.c \
			l3d_ray.c \
			l3d_ray_hit.c \
			l3d_ray_hit_utils1.c \
			l3d_ray_hit_utils2.c \
			l3d_rand.c \
			l3d_obj_read.c \
			l3d_obj_read_utils1.c \
			l3d_obj_read_utils2.c \
			l3d_3d_object.c \
			l3d_3d_object_utils.c \
			l3d_3d_object_transform1.c \
			l3d_3d_object_transform2.c \
			l3d_temp_objects.c \
			l3d_kd_tree.c \
			l3d_kd_tree_node.c \
			l3d_kd_tree_utils.c \
			l3d_fminmax.c \
			l3d_aabb.c \
			l3d_kd_tree_aabb.c \
			l3d_pixel_plot.c \
			l3d_line_draw.c \
			l3d_line_draw_utils1.c \
			l3d_line_draw_utils2.c \
			l3d_image_place.c \
			l3d_color.c \
			l3d_image_read.c \
			l3d_triangle_raster.c \
			l3d_triangle_raster_transparent.c \
			l3d_triangle_raster_utils.c \
			l3d_triangle_raster_pixel.c \
			l3d_triangle_sort.c \
			l3d_triangle_sort_utils.c \
			l3d_shading.c \
			l3d_shading_utils1.c \
			l3d_shading_utils2.c \
			l3d_uv.c \
			l3d_texture_sample.c \
			l3d_baryc.c \
			l3d_triangle_clipping.c \
			l3d_triangle_clipping_clip.c \
			l3d_triangle_clipping_utils.c \
			l3d_procedural_gen.c \
			l3d_buffers.c \
			l3d_buffer_clear.c \
			l3d_shade_luminosity.c \
			l3d_cone_intersection.c

SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
INCLUDES = -I ./include -I $(LIBFT)/include -I $(LIBGMATRIX)/include
CFLAGS = -Wall -Wextra -Werror -march=native -O3 -flto

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
