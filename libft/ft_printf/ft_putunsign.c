/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:30:07 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/11 11:30:16 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsign(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
	{
		len += ft_putunsign(nb / 10);
		len += ft_putunsign(nb % 10);
	}
	if (nb <= 9)
		len += ft_putchar(nb + '0');
	return (len);
}
