/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:15:42 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/29 15:15:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				error_check(int test, const char *message)
{
	if (test)
	{
		ft_dprintf(2, "%s\n", message);
		exit(1);
	}
}
