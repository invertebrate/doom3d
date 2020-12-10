/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:00:25 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:00:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Initializes data that requires initialization before parsin fmt.
*/

static int				init_printf(t_printf *data, int fd)
{
	data->fd = fd;
	data->len = 0;
	if (!(data->buffer = ft_strnew(0)))
		return (false);
	return (true);
}

/*
** Same as ft_printf, but writes to given file descriptor
*/

int						ft_dprintf(int fd, const char *format, ...)
{
	t_printf	data;

	if (!(init_printf(&data, fd)))
		return (false);
	va_start(data.variables, format);
	if (!parse_input(&data, (char*)format))
		return (false);
	va_end(data.variables);
	if (write(data.fd, data.buffer, data.len))
	{
	}
	ft_strdel(&data.buffer);
	return (data.len);
}

/*
** Same as ft_printf, but instead writes the output to inputted char *str
*/

int						ft_sprintf(char *str, const char *format, ...)
{
	t_printf	data;

	if (!(init_printf(&data, 1)))
		return (false);
	va_start(data.variables, format);
	if (!parse_input(&data, (char*)format))
		return (false);
	va_end(data.variables);
	ft_strncpy(str, data.buffer, data.len);
	ft_strdel(&data.buffer);
	return (data.len);
}

/*
** The printf utility formats and prints its arguments, after the first, under
** control of the format.
** The format is a character string which contains three types of objects:
** plain characters, which are simply copied to standard output, character
** escape sequences which are converted and copied to the standard output,
** and format specifications, each of which causes printing of the next
** successive argument.
*/

int						ft_printf(const char *format, ...)
{
	t_printf	data;

	if (!(init_printf(&data, 1)))
		return (false);
	va_start(data.variables, format);
	if (!parse_input(&data, (char*)format))
		return (false);
	va_end(data.variables);
	if (write(data.fd, data.buffer, data.len))
	{
	}
	ft_strdel(&data.buffer);
	return (data.len);
}
