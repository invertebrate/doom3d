/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:01:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/27 16:36:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "ft_dtoa.h"
# include <stdarg.h>

/*
** A data struct containing all flag & fmt token related information
*/

typedef struct		s_printf
{
	va_list		variables;
	char		*spec;
	char		c;
	int			spec_len;
	int			middle_len;
	int			var_len;
	char		*buffer;
	int			len;
	int			fd;
	int			left_justify;
	int			pad_zeros;
	int			show_sign;
	int			blank_space;
	int			zerox;
	int			width;
	int			precision;
	int			has_precision;
	int			type;
	int			is_negative;
	int			is_zero_res;
}					t_printf;

/*
** A data struct used as a helper when looping through ft_printf specs and
** non-token characters (e.g. %u)
*/

typedef struct		s_fmt_specs
{
	int			middle_len;
	int			spec_len;
}					t_fmt_specs;

/*
** Enums for variable length type options in ft_printf spec fmt.
*/

enum				e_lengths
{
	length_none,
	length_hh,
	length_h,
	length_l,
	length_ll,
	length_j,
	length_z,
	length_t,
	length_L
};

int					ft_dprintf(int fd, const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_printf(const char *format, ...);

/*
** Validation
*/

int					is_sub_specifier(char c);
int					is_float_specifier(char c);
int					is_int_specifier(char c);
int					is_flag(char c);

/*
**  Parsing
*/
int					parse_input(t_printf *data, char *fmt);
int					parse_sub_specifiers(t_printf *data);
int					parse_spec_variable_pair(t_printf *data, char *fmt);
int					check_flag(t_printf *data, int *index, int *found_zero);
int					check_length(t_printf *data, int *index, char s);
int					check_parsed_zero(t_printf *data, char *res);

/*
** Number parsing
*/
char				*parse_int(t_printf *data);
char				*parse_float(t_printf *data);
char				*parse_address(t_printf *data);
char				*scientific_double(t_printf *data, long double var);

/*
** String utils
*/
char				*add_str_to_beg(char *str, char *add,
					int len2, int len1);
char				*extend_str(char *str, int size_in, int add_size);
char				*add_chars_to_str_begin(char *res, int start,
					int end, char c);
char				*add_chars_to_str_end(char *res, int start,
					int end, char c);
char				*add_chars_to_null_str_begin(char *res, int start,
					int end, char c);

/*
** Format
*/
char				*handle_formatting(t_printf *data, char *res);
char				*handle_int_padding(t_printf *data, char *res);
char				*handle_float_padding(t_printf *data, char *res);
char				*handle_string_padding(t_printf *data, char *res);
char				*handle_char_padding(t_printf *data, char *res);
char				*handle_int_precision(t_printf *data, char *res);
char				*handle_number_precision(t_printf *data, char *res);
char				*handle_string_precision(t_printf *data, char *res);
void				swap_zerox(t_printf *data, char *res, int x_index);
void				swap_sign_after_padding(t_printf *data, char *res,
					int sign_index);
void				swap_sign_after_precision(t_printf *data, char *res,
					int sign_index);
char				*handle_blank(t_printf *data, char *res);

#endif
