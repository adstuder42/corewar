# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 17:18:56 by xburelle          #+#    #+#              #
#    Updated: 2019/07/13 20:10:48 by xburelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean norme

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCSLC = ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c
SRCSSUP = ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
		  	ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c
SRCSBO = ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c
SRCSUT =	get_next_line.c \
			ft_intlen.c \
			ft_chrinstr.c
OBJECTSLC = $(SRCSLC:.c=.o)
OBJECTSSUP = $(SRCSSUP:.c=.o)
OBJECTSBO = $(SRCSBO:.c=.o)
OBJECTSUT = $(SRCSUT:.c=.o)
INC_PATH	= .
INC_NAME	= libft.h
INC			= $(addprefix $(INC_PATH)/,$(INC_NAME))
NB			= $(words $(SRCSLC), $(SRCSSUP), $(SRCSBO), $(SRCSUT))
INDEX		= 0

all : $(NAME)

$(NAME) : $(OBJECTSLC) $(OBJECTSSUP) $(OBJECTSBO) $(OBJECTSUT) $(INC) Makefile
	@ar rc $@ $^
	@ranlib $@
	@printf "\r\033[32m [100%%] : %s ✓\033[0m\033[K" "LIBFT : $@"

%.o : %.c
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling LIBFT : $<"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean :
	@rm -f $(OBJECTSLC) $(OBJECTSSUP) $(OBJECTSBO) $(OBJECTSUT)
	@printf "\r %s \033[32m✓\033[0m\n" "LIBFT OBJECTS clean"

fclean : clean
	@rm -f $(NAME)
	@printf "\r %s \033[32m✓\033[0m\n" "LIBFT clean"

re : fclean all

norme : 
	norminette $(SRCSLC) $(SRCSSUP) $(SRCSBO) $(SRCSUT)
