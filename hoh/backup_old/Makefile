# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 02:36:10 by ohw               #+#    #+#              #
#    Updated: 2022/04/28 12:44:39 by hoh              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME=minishell
LIBDIR=./libohw
LIBINCSDIR=./libohw/includes
RDLDIR=/Users/hoh/.brew/opt/readline/lib
RDLINCSDIR=/Users/hoh/.brew/opt/readline/include
SRCSDIR=./
INCSDIR=./
SRCS_NAME= minishell.c getpaths.c\
	cd.c draw.c echo.c exit.c\
	env.c env_utils.c\
	export.c pwd.c unset.c
SRCS=$(addprefix $(SRCSDIR), $(SRCS_NAME))

OBJS=${SRCS:.c=.o}

OBJSBNS=${BONUS:.c=.o}

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCSDIR)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBDIR) -L$(RDLDIR) -I$(RDLINCSDIR) -I$(INCSDIR) -lreadline -lohw

clean:
	# make -C $(LIBDIR) clean
	rm -f $(OBJS)

fclean: clean
	# make -C $(LIBDIR) fclean
	rm -f $(NAME)

re: fclean all
