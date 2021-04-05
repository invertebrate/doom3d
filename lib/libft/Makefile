# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2021/04/05 15:20:36 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
DIR_SRC = ./
DIR_OBJ = temp
SOURCES = ft_atoi.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memdel.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_strstr.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isupper.c \
		ft_putchar.c \
		ft_putstr_fd.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_isalpha.c \
		ft_islower.c \
		ft_calloc.c \
		ft_putchar_fd.c \
		ft_strcmp.c \
		ft_strnstr.c \
		ft_toupper.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_itoa_base.c \
		ft_itoa.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strsplit_lst.c \
		ft_lstfold.c \
		ft_lstappend.c \
		ft_realloc.c \
		get_next_line.c \
		ft_isqrt.c \
		ft_sqrt.c \
		ft_strfill.c \
		ft_lstlen.c \
		ft_lmap_int.c \
		ft_lmap_double.c \
		ft_max.c \
		ft_abs.c \
		ft_pixel_foreach.c \
		ft_sort_int_tab.c \
		ft_pow.c \
		ft_match.c \
		ft_strrev.c \
		ft_capitalize.c \
		ft_bzero.c \
		ft_round.c \
		ft_printf/ft_printf.c \
		ft_printf/parse.c \
		ft_printf/parse_specs.c \
		ft_printf/parse_sub_specs.c \
		ft_printf/parse_int.c \
		ft_printf/parse_float.c \
		ft_printf/parse_utils.c \
		ft_printf/string_utils.c \
		ft_printf/format.c \
		ft_printf/format_precision.c \
		ft_printf/format_padding.c \
		ft_printf/format_utils.c \
		ft_printf/validate.c \
		ft_dtoa/ft_dtoa.c \
		ft_dtoa/ft_dtoa_ld.c \
		ft_dtoa/format_normal.c \
		ft_dtoa/format_inf_nan.c \
		ft_dtoa/format_scientific.c \
		ft_dtoa/format_scientific_utils.c \
		ft_dtoa/math_utils.c \
		ft_dtoa/dragon4.c \
		ft_dtoa/dragon4_output.c \
		ft_dtoa/dragon4_values.c \
		ft_dtoa/big_int_add.c \
		ft_dtoa/big_int_divide.c \
		ft_dtoa/big_int_get_set.c \
		ft_dtoa/big_int_mul.c \
		ft_dtoa/big_int_mul_modif.c \
		ft_dtoa/big_int_pow.c \
		ft_dtoa/big_int_shift.c \
		ft_dtoa/big_int_utils.c \
		hash_map/hash_map.c \
		hash_map/hash_map_delete.c \
		hash_map/hash_map_delete_free.c \
		thread_pool/thread_pool.c \
		thread_pool/thread_pool_utils.c \
		radix_sort/radix_sort.c \
		radix_sort/radix_sort_work.c \
		radix_sort/radix_sort_utils.c \
		ft_rand.c \
		read_file.c \
		logger.c \
		ft_atod.c \
		ft_scroll.c \
		ft_error.c \
		ft_max_index.c

SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))

INC=-I./include/

CFLAGS = -Wall -Wextra -Werror -march=native -O3 -flto

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/ft_printf
	@mkdir -p temp/ft_dtoa
	@mkdir -p temp/hash_map
	@mkdir -p temp/thread_pool
	@mkdir -p temp/radix_sort

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

DIR_TESTS = ./tests
TEST_SRCS =$(wildcard $(DIR_TESTS)/*.c)

test:
	@make re
	$(CC) -o test_run $(TEST_SRCS) -I$(DIR_TESTS)/include \
			 -L./ -lft -lpthread $(CFLAGS) $(INC) $(NAME)
	./test_run
	@/bin/rm -f main.o
	@/bin/rm -f test_run
	@make fclean

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
