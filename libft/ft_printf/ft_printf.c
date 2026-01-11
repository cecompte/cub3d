/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:27:30 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/03 17:27:34 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*s)
	{
		len += ft_putchar(*s);
		s++;
	}
	return (len);
}

int	ft_formater(va_list arg, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(arg, int));
	else if (format == 's')
		len += ft_putstr(va_arg(arg, char *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(arg, int));
	else if (format == 'p')
		len += ft_putptr(va_arg(arg, uintptr_t));
	else if (format == 'u')
		len += ft_putunsign(va_arg(arg, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_puthex(va_arg(arg, unsigned int), format);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}	

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;
	int		i;

	va_start(arg, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			len += ft_formater(arg, format[i + 1]);
			i++;
		}
		else if (format[i] == '%')
			break ;
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
