/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:12:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/19 15:41:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include "libft.h"

void		copy_by_8(char *destcpy, const char *srccpy, size_t n);
void		copy_by_7(char *destcpy, const char *srccpy, size_t n);
void		copy_by_6(char *destcpy, const char *srccpy, size_t n);
void		copy_by_5(char *destcpy, const char *srccpy, size_t n);
void		copy_by_4(char *destcpy, const char *srccpy, size_t n);
void		set_by_8(unsigned char *destcpy, int c, size_t n);
void		set_by_7(unsigned char *destcpy, int c, size_t n);
void		set_by_6(unsigned char *destcpy, int c, size_t n);
void		set_by_5(unsigned char *destcpy, int c, size_t n);
void		set_by_4(unsigned char *destcpy, int c, size_t n);

#endif
