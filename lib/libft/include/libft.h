/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:15:47 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/07 21:13:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 50
# define MAX_FD 65536
# define FILE_READ_BUF 65536

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include "t_bool.h"
# include "hash_map.h"
# include "thread_pool.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct	s_pixel_bounds
{
	int			x_start;
	int			x_end;
	int			y_start;
	int			y_end;
}				t_pixel_bounds;

/*
** Assumes little-endian machine.
*/

typedef struct	s_float_bits {
	unsigned long long int		fraction:52;
	unsigned long long int		exp:11;
	unsigned long long int		sign:1;
}				t_float_bits;

typedef union	u_float_dissector {
	double			f;
	t_float_bits	b;
}				t_float_dissector;

typedef struct	s_float_bits_ld {
	unsigned long long int		fraction:63;
	unsigned long long int		intbit:1;
	unsigned long long int		exp:15;
	unsigned long long int		sign:1;
}				t_float_bits_ld;

typedef union	u_float_dissector_ld {
	long double			f;
	t_float_bits_ld		b;
}				t_float_dissector_ld;

typedef struct	s_file_contents
{
	void				*buf;
	uint32_t			size;
	uint32_t			capacity;
}				t_file_contents;

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_tolower(int c);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *str, int fd);
int				ft_atoi(const char *str);
long long int	ft_atoi_long(const char *str);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strncat(char *dst, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			ft_putnbr(int nb);
void			ft_putnbr_unsigned(unsigned int nb);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *str, char c);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list*));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list*));
t_list			*ft_strsplit_lst(char const *str, char c);
void			*ft_lstfold(t_list *lst, void *(*f)(void*, void*));
void			*ft_realloc(void *ptr, size_t size_in, size_t size_out);
void			ft_lstappend(t_list **alst, t_list *new);
int				get_next_line(const int fd, char **line);
int				ft_isqrt(int num);
void			ft_strfill(char **str, char c, size_t len);
float			ft_sqrt(const float x);
size_t			ft_lstlen(t_list *lst);
int				ft_lmap_int(int nb, int *in_minmax, int *out_minmax);
double			ft_lmap_double(double nb, double *in_minmax,
				double *out_minmax);
double			ft_abs(double nb);
double			ft_max_double(double *arr, size_t size);
int				ft_max_int(int *arr, size_t size);
double			ft_min_double(double *arr, size_t size);
int				ft_min_int(int *arr, size_t size);
void			ft_pixel_foreach(t_pixel_bounds *limits,
				void *params, void (*f)(int pixel_i, int x, int y,
				void *params));
void			ft_sort_int_tab(int *tab, unsigned int size, int dir);
long double		ft_abs_long_double(long double nb);
int				ft_match(char *s1, char *s2);
void			ft_strrev(char *str);
size_t			get_num_len(uint64_t nb, uint64_t base);
void			ft_capitalize(char *str);
void			ft_uncapitalize(char *str);
long double		ft_powl(long double nb, int pow);
int				ft_exp_base(long double nb, int base);
char			*ft_strnjoin(char const *s1, char const *s2,
				size_t len1, size_t len2);
double			ft_ceil(double num);
double			ft_floor(double num);
uint32_t		ft_rand(uint32_t seed);
char			*ft_itoa(int32_t nb);
char			*ft_itoa_64(int64_t nb);
char			*ft_itoa_base_32(int32_t nb, int32_t base);
char			*ft_itoa_base_64(int64_t nb, int64_t base);
char			*ft_itoa_base_u32(uint32_t nb, uint32_t base);
char			*ft_itoa_base_u64(uint64_t nb, uint64_t base);
double			ft_atod(char *str);

/*
** Expose ft_printf functions via libft.h
*/

int				ft_dprintf(int fd, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_printf(const char *format, ...);

void			destroy_file_contents(t_file_contents *f);
t_file_contents	*read_file(const char *filename);
void			ft_scroll_over(char **str, char c);
void			ft_scroll_to(char **str, char c);

void			error_check(int test, const char *message);

double			ft_max_double_idx(double *arr, size_t size, size_t *index);
int				ft_max_int_idx(int *arr, size_t size, size_t *index);
double			ft_min_double_idx(double *arr, size_t size, size_t *index);
int				ft_min_int_idx(int *arr, size_t size, size_t *index);

#endif
