/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:10 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/29 09:02:39 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"

//	TODO:
//		- parsing line
//		- creating abstract syntax tree
//		- error handling

typedef enum e_error_type
{
	SYNTAX,
	SYS,
}	t_error_type;

typedef enum e_token_type
{
	CMD,
	ARGS,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	END,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	int		len;
}	t_token_list;

// parse.c
t_token_list	*tokenize(const char *src);

// token_list.c
t_token_list	*new_token_list();
void			destroy_token_list(t_token_list *l);
t_token			*new_token(char *str, t_token_type t);
void			append_token(t_token_list *l, t_token *ele);

// errors.c
void	exit_with_error(const char *msg, t_error_type et);

#endif // PARSE_H