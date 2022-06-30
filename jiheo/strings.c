/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:26:07 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/28 13:38:12 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// single_strcpy 함수는 src 문자열에서 인덱스가 from ~ to인 전체 문자열을 반환
char	*single_strcpy(const char *src, int from, int to)
{
	const int	size = to - from + 1;
	char		*new_str;
	const int	start_i = from;

	new_str = (char *)malloc(size * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (from <= to)
		new_str[from - start_i] = src[from++];
	return (new_str);
}

static
char	*get_env_value(const char *src, int start_i, int end_i)
{
	char	*key;
	char	*res;
	int		i;

	key = (char *)malloc((end_i - start_i + 2) * sizeof(char));
	if (key == NULL)
		return (NULL);
	i = 0;
	while (i + start_i <= end_i)
	{
		key[i] = src[i + start_i];
		i++;
	}
	key[i] = 0;
	res = getenv(key);
	free(key);
	return (res);
}

static
int	get_end_i(const char *src, int start_i)
{
	while (src[start_i] && ft_isalnum((int)src[start_i]))
		start_i++;
	return (start_i);
}

// double_strcpy 함수는 src 문자열에서 인덱스가 from ~ to인 ${}를 변환하여 문자열을 반환
char	*double_strcpy(const char *src, int from, int to)
{
	char	*new_str;
	int		end_i;
	int		tmp_i;
	char	*val;

	tmp_i = 0;
	while (from <= to)
	{
		if (src[from] == '$')
		{
			end_i = get_end_i(src, from + 1);
			strcat(&new_str, get_env_value(src, from + 1, end_i));
		}
		else
		{
			tmp_i = from;
			while (src[from] && src[from] != '$')
				from++;
			val = single_strcpy(src, tmp_i, from - 1);
			strcat(&new_str, val);
			free(val);
		}
	}
	return (new_str);
}
