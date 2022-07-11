/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:01:45 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 20:11:13 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree.h"

static
char	*ts_env(char *s, int *i)
{
	char	*key;
	char	*val;
	int		s_i;

	key = NULL;
	s_i = ++(*i);
	while (s[*i] && ft_isalnum(s[*i]))
		(*i)++;
	if (s_i == *i)
		return (ft_strdup("$"));
	key = ft_substr(s, s_i, *i - s_i);
	if (key == NULL)
		return (NULL);
	val = getenv(key);
	free(key);
	if (val == NULL)
		return (NULL);
	return (ft_strdup(val));
}

char	*translate(char *s)
{
	char	*tmp;
	int		i;
	int		s_i;
	char	*res;

	i = 0;
	res = NULL;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
			tmp = ts_env(s, &i);
		else
		{
			s_i = i;
			while (s[i] && s[i] != '$')
				i++;
			tmp = ft_substr(s, s_i, i - s_i);
		}
		res = join_and_rm_all(res, tmp);
	}
	free(s);
	s = NULL;
	return (res);
}
