CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c99 -I.
NAME = libft.a
HEADERS = ./libft.h
SRCS = ./ft_bzero.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c \
			./ft_memchr.c ./ft_memcmp.c ./ft_memmove.c ./ft_memset.c ./ft_strchr.c ./ft_strrchr.c ./ft_strlen.c \
			./ft_strncmp.c ./ft_tolower.c ./ft_toupper.c ./ft_strlcat.c ./ft_strlcpy.c ./ft_memcpy.c\
			./ft_strnstr.c ./ft_atoi.c ./ft_strdup.c ./ft_calloc.c ./ft_substr.c ./ft_strjoin.c \
			./ft_strtrim.c ./ft_split.c ./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c \
			./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c
OBJECTS = $(SRCS:%.c=%.o)
BONUS = ./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c ./ft_lstlast.c ./ft_lstadd_back.c\
			./ft_lstclear.c ./ft_lstiter.c
BONUSOBJS = $(BONUS:%.c=%.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJECTS) $(BONUSOBJS)
else
	OBJ_FILES = $(OBJECTS)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

bonus :
	make WITH_BONUS=1 all
	
clean:
	find . -name "*.o" -delete

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
