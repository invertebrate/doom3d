/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:57:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:17:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_putstr_fd() writes a given string into given file descriptor.
*/

void	ft_putstr_fd(char const *str, int fd)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (write(fd, str, len))
	{
	}
}
