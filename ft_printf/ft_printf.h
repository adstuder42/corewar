/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 05:53:37 by schabbi           #+#    #+#             */
/*   Updated: 2018/11/08 22:41:22 by schabbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUF_SIZE 100
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <wchar.h>
# include <string.h>
# include <stdint.h>
# include <wchar.h>

typedef	struct	s_t_buffer
{
	char		str[BUF_SIZE];
	int			buf_len;
	int			str_len;
}				t_buffer;

void			ft_first_byte(int *mask, char *tab, int *size, int *fl);
void			flagtheflags_3(int *fl, int *conv);
int				is_sub_arr(uintmax_t big_nbr, uintmax_t div
					, int *fl, double nbr);
int				ft_putwstr_onbuf(t_buffer *buf, int *fl, int str_len
					, wchar_t *str);
uintmax_t		ft_power(uintmax_t nbr1, uintmax_t nbr2);
int				ft_flt(t_buffer *buf, int width, int *fl, va_list ls);
int				ft_bin(t_buffer *buf, int width, int *fl, va_list ls);
int				count_bits(uintmax_t nbr, int base);
size_t			ft_wstrlen(const wchar_t *str, int precision);
int				big_s(t_buffer *buf, int width, int *fl, va_list ls);
int				check_valid_flag(char c);
int				big_c(t_buffer *buf, int width, int *fl, va_list ls);
void			ft_putchar(char c);
int				ft_s(t_buffer *buf, int width, int *flags, va_list ls);
void			ft_cast(int *fl, long long *d_, va_list ls);
int				ft_putstr_onbuf(t_buffer *buf, char *str,
					long long int buf_len);
void			flagtheflags_2(int *flags, char *tmp, int converter);
void			ft_tolowercase(char *str);
char			*ft_itoabase(uintmax_t nbr, int base);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
void			ft_putstr(const char *str);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc(size_t size);
void			ft_bzero(void *b, size_t len);
int				ft_atoi(const char *str);
int				ft_putchar_onbuf (t_buffer *buf, char c);
int				solve_format(const char *restrict format,
					va_list ls, t_buffer *buf);
int				print_part(const char *restrict format, int *i,
				t_buffer *buf, va_list ls);
void			rv_width(t_buffer *buf, int width, int *flags);
int				d(t_buffer *buf, int width, int *flags, va_list ls);
int				ch(t_buffer *buf, int width, int *flags, va_list ls);
char			*ft_itoa(int n);
int				ft_printf(const char *restrict format, ...);

#endif
