/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/23 12:28:53 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_free_split_k_q_s(char **d, int start)
{
	start--;
	while (start >= 0)
	{
		free(d[start]);
		start--;
	}
	free(d);
	return (0);
}

int	check_quotes(char const *s, char q)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == q)
			quotes++;
		i++;
	}
	return (quotes % 2 == 0);
}

int	ft_calc_k_q_s(int i, int diff, char _c, char const *_s) // trop de lignes
{
	int	j;

	j = 0;
	if (diff == 1)
	{
		while (_s[i] != _c && _s[i])
		{
			j = i + 1;
			if (_s[i] == 34 || _s[i] == 39)
			{
				while (_s[j] != _s[i] && _s[j])
					j++;
				i = j + 1;
			}
			else
				i++;
		}
	}
	else if (diff == 0)
	{
		while (_s[i] == _c && _s[i])
			i++;
	}
	return (i);
}

int	count_words(char *no_space)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (!check_quotes(no_space, 34) || !check_quotes(no_space, 39))
		return (-1);
	while (no_space[i])
	{
		if (ft_isspace(no_space[i]) == 1)
		{
			word++;
			i++;
		}
		if (no_space[i] == 34 || no_space[i] == 39)
		{
			i++;
			while (no_space[i] && (no_space[i] != 34 && no_space[i] != 39))
				i++;
			word++;
		}
		i++;
	}
	return (word + 1);
}

int	check_open_quotes(char const *s)
{
	int i;
	int s_qts;
	int d_qts;

	i = 0;
	s_qts = 0;
	d_qts = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
			{
				printf("s_qts on 1 -> s[i] : %c | i : %d\n", s[i], i);
				s_qts = 1;
				i++;
			}
			else if (s[i] == '"')
			{
				printf("d_qts on 1 -> s[i] : %c | i : %d\n", s[i], i);
				d_qts = 1;
				i++;
			}
		}
		if (s_qts == 1)
		{
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] == '\'')
			{
				printf("s_qts on 0 -> s[i] : %c | i : %d\n", s[i], i);
				s_qts = 0;
				i++;
			}
		}
		else if (d_qts == 1)
		{
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] == '"')
			{
				printf("s_qts on 0 -> s[i] : %c | i : %d\n", s[i], i);
				d_qts = 0;
				i++;
			}
		}
		printf("s[i] : %c | i : %d\n", s[i], i);
		//if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	printf("s_qts : %d| d_qts : %d\n", s_qts, d_qts);
	if (s_qts == 1 || d_qts == 1)
		return (0);
	return (1);
}

char	**ft_split_k_q_s(t_main *main, char const *s, char c) // trop de lignes
{
	int		i;
	int		j;
	int		x;
	char	**dest;
	char	*no_space;
	int		size;

	i = 0;
	x = 0;
	j = 0;
	no_space = get_rid_of_spaces(s);
	if (check_open_quotes(no_space) == 0)
		return (NULL);
	printf("ouch\n");
	exit(0);
	size = count_words(no_space);
	printf("size : %d\n", size);
	if (size <= 0)
		return (NULL);
	replace_dollar(no_space, main);
	printf("no space : %s\n", no_space);
	exit(0);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (free(no_space), NULL);
	while (no_space[i])
	{
		i = ft_calc_k_q_s(i, 0, c, no_space);
		j = ft_calc_k_q_s(i, 1, c, no_space);
		dest[x] = get_rid_of_quotes(ft_substr(no_space, i, j - i));
		if (dest[x++] == NULL || j < 0)
			return (ft_free_split_k_q_s(dest, x));
		i += (j - i);
	}
	dest[x] = 0;
	main->split_len = x;
	return (free(no_space), dest);
}
