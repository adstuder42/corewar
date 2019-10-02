.PHONY: all re clean fclean norme

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
#FLAGS		= -Wall -Wextra -Werror  \
			  -g -fsanitize=address	\
			  -fno-omit-frame-pointer		\
			  -fsanitize-address-use-after-scope \

NAME		= libftprintf.a
SRC_PATH	= ./src
SRC_NAME	= ft_printf.c \
				chars.c \
				numbers.c \
				functionalities.c \
				functionalities_2.c \
				bonus.c

SRC			= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ_PATH	= ./obj
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
LIB_PATH	= ./libft_printf
LIB_NAME	= ft_strdup.c \
				ft_putstr.c \
				ft_strlen.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_memalloc.c \
				ft_memset.c \
				ft_itoabase.c \
				ft_tolowercase.c \
				ft_putchar.c \
				ft_wstrlen.c \
				ft_power.c

LIB 		= $(addprefix $(LIB_PATH)/, $(LIB_NAME))
OBJLIB_PATH	= ./obj
OBJLIB_NAME	= $(LIB_NAME:.c=.o)
OBJLIB		= $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))
INC_PATH	= ./include
INC_NAME	= ft_printf.h
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
NB			= $(words $(SRC), $(LIB))
INDEX		= 0

all : $(NAME)

$(NAME) : $(OBJ) $(OBJLIB)
	@ar rc $(NAME) $(OBJ) $(OBJLIB)
	@ranlib $(NAME)
	@printf "\r\033[32m [100%%] : %s ✓\033[0m\033[K" "FT_PRINTF : $@"

$(OBJ_PATH) :
	@mkdir -p $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling FT_PRINTF : $<"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c | $(OBJ_PATH)
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling FT_PRINTF : $<"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean :
	@rm -f $(OBJ) $(OBJLIB)
	@printf "\r %s \033[32m✓\033[0m\n" "FT_PRINTF Objects clean"

fclean : clean
	@rm -f $(NAME)
	@printf "\r %s \033[32m✓\033[0m\n" "FT_PRINTF clean"

re : fclean all

out : re
	gcc $(FLAGS) main.c libftprintf.a
	./a.out

outsf : re
	    gcc $(FLAGS) main.c libftprintf.a -g
		  

outnoflag : re
	gcc main.c libftprintf.a
	./a.out

norme : 
	norminette $(SRC) $(LIB) $(INC)

#curq :
#	cp libftprintf.a ../curqui_test/libftprintf.a

