/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:54:27 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:17:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_putstr_fd() writes a given string into stdout.
*/

void	ft_putstr(char const *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (write(1, str, len))
	{
	}
}
