/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:29:11 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/11 11:29:20 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_hex(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

int	ft_puthex(unsigned int arg, char format)
{
	int	len;

	len = 0;
	if (arg >= 16)
	{
		len += ft_puthex((arg / 16), format);
		len += ft_puthex((arg % 16), format);
	}
	else
	{
		if (arg <= 9)
			len += ft_putchar(arg + '0');
		else
			if (format == 'x')
				len += ft_putchar(arg - 10 + 'a');
		else if (format == 'X')
				len += ft_putchar(arg - 10 + 'A');
	}
	return (len);
}
