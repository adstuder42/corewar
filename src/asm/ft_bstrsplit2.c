/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstrsplit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:33:11 by xburelle          #+#    #+#             */
/*   Updated: 2019/09/21 12:13:42 by xburelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		nb_words(char const *s, char *delimiter)
{
	int		i;
	int		flag;
	int		nb;

	i = 0;
	nb = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_strchr(delimiter, s[i]))
			i++;
		while (s[i] != '\0' && !ft_strchr(delimiter, s[i]))
		{
			i++;
			flag = 1;
		}
		while (s[i] != '\0' && ft_strchr(delimiter, s[i]))
			i++;
		if (flag == 1)
		{
			nb++;
			flag = 0;
		}
	}
	return (nb);
}

static int		*nb_letters(char const *s, char *delimiter, int nb_words)
{
	int		i[2];
	int		j;
	int		*tab;

	i[0] = 0;
	i[1] = 0;
	if (!(tab = (int *)malloc(sizeof(int) * (nb_words))))
		return (NULL);
	while (s[i[0]] != '\0')
	{
		j = 0;
		while (s[i[0]] != '\0' && ft_strchr(delimiter, s[i[0]]))
			i[0]++;
		while (s[i[0]] != '\0' && !ft_strchr(delimiter, s[i[0]]))
		{
			i[0]++;
			j++;
		}
		while (s[i[0]] != '\0' && ft_strchr(delimiter, s[i[0]]))
			i[0]++;
		if (j > 0)
			tab[i[1]] = j;
		i[1]++;
	}
	return (tab);
}

static void		free_tab(char **tab, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
		free(tab[i++]);
	free(tab);
}

static int		populate(t_stab tab, int *tab_letters, char const *s,
	char *delimiter)
{
	int		letter;
	int		i;
	int		nchar;

	i = 0;
	nchar = 0;
	while (i < tab.nb)
	{
		if (!(tab.s[i] = (char *)malloc(sizeof(char) * (tab_letters[i] + 1))))
		{
			free_tab(tab.s, i);
			return (0);
		}
		while (s[nchar] != '\0' && ft_strchr(delimiter, s[nchar]))
			nchar++;
		letter = 0;
		while (s[nchar] != '\0' && !ft_strchr(delimiter, s[nchar]))
			tab.s[i][letter++] = s[nchar++];
		while (s[nchar] != '\0' && ft_strchr(delimiter, s[nchar]))
			nchar++;
		tab.s[i][letter] = '\0';
		i++;
	}
	tab.s[i] = NULL;
	return (1);
}

char			**ft_bstrsplit2(char const *s, char *delimiter)
{
	t_stab	tab;
	int		*tab_letters;

	tab.s = NULL;
	if (s == NULL)
		return (tab.s);
	tab.nb = nb_words(s, delimiter);
	if (!(tab.s = (char **)malloc(sizeof(char *) * (tab.nb + 1))))
		return (NULL);
	if (!(tab_letters = nb_letters(s, delimiter, tab.nb)))
	{
		free(tab.s);
		return (NULL);
	}
	if (!(populate(tab, tab_letters, s, delimiter)))
	{
		free(tab_letters);
		return (NULL);
	}
	free(tab_letters);
	return (tab.s);
}
