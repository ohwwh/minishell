/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:00:21 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/07 21:50:24 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

// #include "Libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_signal
{
    int     s_int;
    int     quit;
    int     stat;
    pid_t   pid;
}   t_signal;

void    c_handler(int sig);
void    d_handler(int sig);
void    bs_handler(int sig);

#endif