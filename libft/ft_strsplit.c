/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:08:55 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 13:52:59 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_words(char const *s, char c)
{
	int		i;
	int		flag;
	int		nb;

	i = 0;
	nb = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			i++;
			flag = 1;
		}
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (flag == 1)
		{
			nb++;
			flag = 0;
		}
	}
	return (nb);
}

static int		*nb_letters(char const *s, char c, int nb_words)
{
	int		i;
	int		j;
	int		nb;
	int		*tab;

	i = 0;
	nb = 0;
	if (!(tab = (int *)malloc(sizeof(int) * (nb_words))))
		return (NULL);
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			i++;
			j++;
		}
		while (s[i] != '\0' && s[i] == c)
			i++;
		tab[nb] = j - 1;
		nb++;
	}
	return (tab);
}

static int		populate(char *tab, int nchar, char const *s, char c)
{
	int		letter;

	while (s[nchar] != '\0' && s[nchar] == c)
		nchar++;
	letter = 0;
	while (s[nchar] != '\0' && s[nchar] != c)
		tab[letter++] = s[nchar++];
	while (s[nchar] != '\0' && s[nchar] == c)
		nchar++;
	tab[letter] = '\0';
	return (nchar);
}

char			**ft_strsplit(char const *s, char c)
{
	int		nb;
	char	**tab;
	int		i;
	int		*tab_letters;
	int		k;

	tab = NULL;
	if (s == NULL)
		return (tab);
	nb = nb_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	i = 0;
	k = 0;
	tab_letters = nb_letters(s, c, nb);
	while (i < nb)
	{
		if (!(tab[i] = (char *)malloc(sizeof(char) * (tab_letters[i] + 1))))
			return (NULL);
		k = populate(tab[i], k, s, c);
		i++;
	}
	free(tab_letters);
	tab[i] = NULL;
	return (tab);
}
