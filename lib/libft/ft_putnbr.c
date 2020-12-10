/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:38:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/24 20:37:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_putnbr_fd() writes a given integer into stdout.
*/

void	ft_putnbr(int nb)
{
	int	digits[10];
	int	index;
	int sign;

	index = 0;
	sign = nb >= 0 ? 1 : -1;
	if (nb == false)
		ft_putchar('0');
	while (nb != 0)
	{
		digits[index] = nb % 10;
		nb = nb / 10;
		index++;
	}
	index++;
	if (sign < 0)
		ft_putchar('-');
	while (--index > 0)
		ft_putchar(sign * digits[index - 1] + '0');
}

void	ft_putnbr_unsigned(unsigned int nb)
{
	unsigned int	digits[10];
	int				index;

	index = 0;
	if (nb == false)
		ft_putchar('0');
	while (nb != 0)
	{
		digits[index] = nb % 10;
		nb = nb / 10;
		index++;
	}
	index++;
	while (--index > 0)
		ft_putchar(digits[index - 1] + '0');
}
