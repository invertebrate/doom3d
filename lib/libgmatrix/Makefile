# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:09:18 by ohakola           #+#    #+#              #
#    Updated: 2021/05/09 17:48:00 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libgmatrix.a
LIBFT = ../libft
DIR_SRC = ./
DIR_TESTS = ./tests
DIR_OBJ = temp
SOURCES = ml_matrix4_id.c \
			ml_matrix4_inverse.c \
			ml_matrix4_mul.c \
			ml_matrix4_mul_vec.c \
			ml_matrix4_projection.c \
			ml_matrix4_rotation.c \
			ml_matrix4_general_rotation.c \
			ml_matrix4_rotate.c \
			ml_matrix4_view.c \
			ml_print1.c \
			ml_print2.c \
			ml_rad.c \
			ml_vector3_add.c \
			ml_vector3_cross.c \
			ml_vector3_dot.c \
			ml_vector3_forward.c \
			ml_vector3_mag.c \
			ml_vector3_mul.c \
			ml_vector3_normalize.c \
			ml_vector3_sub.c \
			ml_vector3_to_vec4.c \
			ml_vector4_add.c \
			ml_vector4_cross.c \
			ml_vector4_dot.c \
			ml_vector4_mag.c \
			ml_vector4_mul.c \
			ml_vector4_normalize.c \
			ml_vector4_sub.c \
			ml_vector_copy.c \
			ml_vector_set.c \
			ml_vector2_mag.c \
			ml_vector2_sub.c \
			ml_vector2_normalize.c \
			ml_vector2_mul.c \
			ml_vector2_dot.c \
			ml_vector2_add.c \
			ml_matrix4_translation.c \
			ml_matrix4_copy.c \
			ml_matrix3_create.c \
			ml_matrix3_mul_vec3.c

SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))
INCLUDES = -I ./include -I ../external_log -I $(LIBFT)/include
CFLAGS = -Wall -Wextra -Werror -march=native -O3 -flto

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

TEST_SRCS =$(wildcard $(DIR_TESTS)/*.c)

test: all
	@make -C $(LIBFT)
	$(CC) -o test_run $(TEST_SRCS) \
	-I./tests/include -L$(LIBFT) -lft $(CFLAGS) $(INCLUDES) $(NAME)
	./test_run
	@/bin/rm -f main.o
	@/bin/rm -f test_run
	@make fclean
	@make -C $(LIBFT) fclean

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
