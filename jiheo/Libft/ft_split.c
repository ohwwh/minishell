/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:43:28 by jiheo             #+#    #+#             */
/*   Updated: 2021/11/22 16:19:58 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_s(const char *s, char c)
{
	char	*s_copied;
	size_t	idx;

	s_copied = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (s_copied == NULL)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (*s != c)
			s_copied[idx++] = *(s++);
		else
		{
			while (*s == c)
				s++;
			if (*s != 0)
				s_copied[idx++] = c;
		}
	}
	s_copied[idx] = 0;
	return (s_copied);
}

static void	update_res(const char *new_s, char **res, char c)
{
	const char	*tmp;
	size_t		len;
	size_t		size_idx;

	len = 0;
	size_idx = 0;
	while (*new_s)
	{
		tmp = new_s;
		len = 0;
		while (*new_s && *new_s != c)
		{
			len++;
			new_s++;
		}
		res[size_idx++] = ft_substr(tmp, 0, len);
		if (*new_s)
			new_s++;
	}
	res[size_idx] = NULL;
}

static size_t	count_c(char *s, char c)
{
	size_t	c_cnt;

	c_cnt = 0;
	while (*s)
	{
		if (*s == c)
			c_cnt++;
		s++;
	}
	return (c_cnt);
}

static char	*init_split(const char *s, char c, size_t *c_cnt, int *err)
{
	char	*new_s;

	*err = 0;
	if (s == NULL || *s == 0)
		return (NULL);
	while (*s == c)
		s++;
	if (*s == 0)
		return (NULL);
	new_s = trim_s(s, c);
	if (new_s == NULL || *new_s == 0)
	{
		if (new_s != NULL)
			free(new_s);
		else
			*err = 1;
		return (NULL);
	}
	*c_cnt = count_c(new_s, c);
	return (new_s);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	c_cnt;
	char	*new_s;
	int		err;

	if (s == NULL)
		return (NULL);
	new_s = init_split(s, c, &c_cnt, &err);
	if (new_s == NULL)
	{
		if (err)
			return (NULL);
		res = (char **)malloc(sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	res = (char **)malloc((c_cnt + 2) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	update_res(new_s, res, c);
	free(new_s);
	return (res);
}
