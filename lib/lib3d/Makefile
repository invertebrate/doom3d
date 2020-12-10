# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#              #
#    Updated: 2020/12/10 14:09:11 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = lib3d.a
LIBFT = ../libft
LIBGMATRIX = ../libgmatrix
DIR_SRC = ./
DIR_OBJ = temp
SOURCES = l3d_triangle.c \
			l3d_triangle_copy.c \
			l3d_triangle_update.c \
			l3d_triangle_vector.c \
			l3d_ray.c \
			l3d_ray_hit.c \
			l3d_ray_hit_utils.c \
			l3d_rand.c \
			l3d_obj_read.c \
			l3d_obj_read_utils1.c \
			l3d_obj_read_utils2.c \
			l3d_3d_object.c \
			l3d_3d_object_utils.c \
			l3d_3d_object_transform.c \
			l3d_temp_objects.c \
			l3d_kd_tree.c \
			l3d_kd_tree_node.c \
			l3d_kd_tree_utils.c \
			l3d_fminmax.c \
			l3d_aabb.c \
			l3d_kd_tree_aabb.c \
			l3d_pixel_plot.c \
			l3d_line_draw.c \
			l3d_image_place.c \
			l3d_color.c \
			l3d_image_read.c \
			l3d_triangle_raster.c \
			l3d_triangle_raster_utils.c \
			l3d_triangle_raster_pixel.c \
			l3d_shading.c \
			l3d_uv.c \
			l3d_texture_sample.c \
			l3d_baryc.c \
			l3d_triangle_clipping.c \
			l3d_triangle_clipping_clip.c \
			l3d_triangle_clipping_utils.c \
			l3d_procedural_gen.c \
			l3d_buffers.c \
			l3d_buffer_clear.c

SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))
INCLUDES = -I ./include -I $(LIBFT)/include -I $(LIBGMATRIX)/include
CFLAGS = -Wall -Wextra -Werror
OPTIMIZED_CFLAGS = -Wall -Wextra -Werror -O3 -flto

all: $(DIR_OBJ) $(NAME)

dev: $(DIR_OBJ) $(NAME)_dev

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(NAME)_dev: $(DEV_OBJS)
	@ar rc $(NAME) $(DEV_OBJS)

$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(OPTIMIZED_CFLAGS) $(INCLUDES) -c -o $@ $<

$(DIR_OBJ)/%_dev.o: $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
