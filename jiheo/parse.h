/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:10 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 19:51:46 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"

typedef enum e_error_type
{
	SYNTAX,
	SYS,
}	t_error_type;

typedef enum e_token_type
{
	CMD,
	WORD,
	PIPE,
	REDIR,
	NONE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_map
{
	char	*key;
	char	*value;
}	t_map;

t_map	*g_envs;

// parse.c
t_token	*tokenize(const char *src);

// strings.c
char	*single_strcpy(const char *src, int from, int to);
char	*double_strcpy(const char *src, int from, int to);

// envs.c
char	*get_env(const char *key);

// utils.c
void	strcat(char **dst, const char *src);

// errors.c
void	exit_with_error(const char *msg, t_error_type et);

#endif // PARSE_H