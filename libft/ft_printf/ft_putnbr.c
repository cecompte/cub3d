/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:28:39 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/11 11:28:46 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	int	len;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		len = 11;
		return (len);
	}
	len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-');
		len += ft_putnbr(-nb);
		return (len);
	}
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10);
		len += ft_putnbr(nb % 10);
	}
	if (nb <= 9)
		len += ft_putchar(nb + '0');
	return (len);
}
