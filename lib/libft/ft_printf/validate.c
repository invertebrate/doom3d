/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:13:32 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 16:58:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** This file contains helper functions to validate inputs.
*/

int						is_int_specifier(char c)
{
	return (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U' ||
			c == 'o' || c == 'O' || c == 'x' || c == 'X' || c == 'b');
}

int						is_float_specifier(char c)
{
	return (c == 'f' || c == 'F' || c == 'e' || c == 'E' ||
		c == 'g' || c == 'G');
}

int						is_flag(char c)
{
	return (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0');
}

int						is_sub_specifier(char c)
{
	return (is_flag(c) || c == 'h' || c == 'l' || c == 'j' ||
			c == 'z' || c == 't' || c == 'L' || ft_isdigit(c) ||
			c == '.' || c == '*' || c == '\'');
}
