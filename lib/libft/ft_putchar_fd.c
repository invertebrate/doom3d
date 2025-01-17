/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:58:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:56:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_putchar_fd() writes a character into given file descriptor
*/

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1))
	{
	}
}
