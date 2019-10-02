# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xburelle <xburelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 14:46:19 by xburelle          #+#    #+#              #
#    Updated: 2019/09/21 13:10:18 by xburelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ifndef NOTVERBOSE
MAKEFLAGS += --no-print-directory
#endif

.PHONY: all re clean fclean norme

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
# Mac
	ID_UN		:=	$(shell id -un)
	SDLINCDIR	=	/Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2\
					/Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2\
	SDL			=	$(shell sdl2-config --libs)\
	SDL_MIXER	=	-L/Users/$(ID_UN)/.brew/lib -lSDL2_mixer
else
# Linux
	SDLINCDIR	= #nothing
	SDL			= $(shell sdl2-config --libs)
	SDL_MIXER	= -lSDL2_mixer
endif

SDLINC		= $(foreach dir, $(SDLINCDIR), -I$(dir))

C			= gcc
FLAGS		= -Wall -Wextra -Werror
NCURSES		= -lcurses
SDL			= $(shell sdl2-config --libs)
SDL_MIXER	= -lSDL2_mixer
NAME		= corewar
LIBFT_PATH	= ./libft
LIBFT_NAME	= libft.a
LIBFT		= $(addprefix $(LIBFT_PATH)/, $(LIBFT_NAME))
FT_PRINTF_PATH	= ./ft_printf
FT_PRINTF_NAME	= libftprintf.a
FT_PRINTF		= $(addprefix $(FT_PRINTF_PATH)/, $(FT_PRINTF_NAME))
ASM_NAME		= asm
ASM_PATH	= ./src/asm
ASM_CORE_NAME	= ft_basename.c \
				ft_bstrsplit2.c \
				ft_strndup.c \
				ft_atolli.c \
				ft_isext.c \
				asm.c \
				asm_lexer.c \
				asm_inst_utils.c \
				asm_labels_utils.c \
				asm_read_utils.c \
				asm_read.c \
				asm_error.c \
				asm_error2.c \
				asm_error3.c \
				asm_free.c \
				asm_usage.c
ASM_CORE			= $(addprefix $(ASM_PATH)/, $(ASM_CORE_NAME))
ASM_CHECK_PATH	= $(ASM_PATH)/check
ASM_CHECK_NAME	= asm_check.c \
				asm_check_insts1.c \
				asm_check_insts2.c \
				asm_check_insts3.c \
				asm_check_insts4.c \
				asm_check_labels.c
ASM_CHECK		= $(addprefix $(ASM_CHECK_PATH)/, $(ASM_CHECK_NAME))
ASM_PARSE_PATH	= $(ASM_PATH)/parse
ASM_PARSE_NAME	= asm_parse_header.c \
				asm_parse.c \
				asm_parse_params.c \
				asm_parse_utils.c
ASM_PARSE		= $(addprefix $(ASM_PARSE_PATH)/, $(ASM_PARSE_NAME))
ASM_TRANSLATE_PATH	= $(ASM_PATH)/translation
ASM_TRANSLATE_NAME	= asm_translation.c \
				asm_translate_insts1.c \
				asm_translate_insts2.c \
				asm_translate_insts3.c \
				asm_translate_insts4.c \
				asm_translate_buf.c \
				asm_translate_buf2.c \
				asm_translate_header.c \
				asm_translate_params.c \
				asm_translate_labcall.c
ASM_TRANSLATE		= $(addprefix $(ASM_TRANSLATE_PATH)/, $(ASM_TRANSLATE_NAME))
SRC_PATH	= ./src
SRC_NAME	= vm.c \
			ft_itoa_base2.c \
		  display.c\
		  parsing_arg.c\
		  parsing_player_num.c\
		  war.c\
		  the_reaper.c\
		  instr_2.c\
		  instr_3.c \
		  parse_arg_instr.c\
		  tools.c\
		  uncoded_instruct.c \
		  live_manager.c \
		  live_manager_2.c \
		  instr_4.c \
		  instr_1.c \
		  vm_check_instr_1.c \
		  vm_check_instr_2.c \
		  vm_check_instr_3.c \
		  vm_check_instr_4.c \
		  tools_1.c
SRC			= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
NCURSES_SRC_PATH	= $(SRC_PATH)/ncurses
NCURSES_SRC_NAME	= ncurses_arena.c \
						ncurses_init.c \
						ncurses_quit.c \
						ncurses_side.c \
						ncurses_side_2.c \
						ncurses_utils.c \
						ncurses_war.c
NCURSES_SRC			= $(addprefix $(NCURSES_SRC_PATH)/, $(NCURSES_SRC_NAME))
OBJ_NCURSES_NAME	= $(NCURSES_SRC_NAME:.c=.o)
OBJ_NCURSES			= $(addprefix $(OBJ_PATH)/, $(OBJ_NCURSES_NAME))

LIBFT_HEADERS = $(LIBFT_DIRECTORY)/
FT_PRINTF_HEADERS = $(FT_PRINTF_DIRECTORY)/
ASM_INCLUDES = -I$(INC) \
	-I$(LIBFT_HEADERS) \
	-I$(FT_PRINTF_HEADERS)
ASM_HEADERS_NAME = op.h \
				asm.h
ASM_HEADERS = $(addprefix $(INC)/, $(ASM_HEADERS_NAME))
OBJ_PATH	= ./obj
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ_PATH			= ./obj
ASM_OBJ_CORE_PATH	= $(OBJ_PATH)/asm
ASM_OBJ_CORE_NAME	= $(ASM_CORE_NAME:.c=.o)
ASM_OBJ_CORE		= $(addprefix $(ASM_OBJ_CORE_PATH)/, $(ASM_OBJ_CORE_NAME))
ASM_OBJ_CHECK_PATH	= $(ASM_OBJ_CORE_PATH)/check
ASM_OBJ_CHECK_NAME	= $(ASM_CHECK_NAME:.c=.o)
ASM_OBJ_CHECK		= $(addprefix $(ASM_OBJ_CHECK_PATH)/, $(ASM_OBJ_CHECK_NAME))
ASM_OBJ_PARSE_PATH	= $(ASM_OBJ_CORE_PATH)/parse
ASM_OBJ_PARSE_NAME	= $(ASM_PARSE_NAME:.c=.o)
ASM_OBJ_PARSE		= $(addprefix $(ASM_OBJ_PARSE_PATH)/, $(ASM_OBJ_PARSE_NAME))
ASM_OBJ_TRANSLATE_PATH	= $(ASM_OBJ_CORE_PATH)/translate
ASM_OBJ_TRANSLATE_NAME	= $(ASM_TRANSLATE_NAME:.c=.o)
ASM_OBJ_TRANSLATE		= $(addprefix $(ASM_OBJ_TRANSLATE_PATH)/, $(ASM_OBJ_TRANSLATE_NAME))
OBJ_ASM_NAME = $(ASM_NAME:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
INC			= ./inc
INC_NAME	= vm.h
COREWAR_HEADERS = $(addprefix $(INC)/, $(INC_NAME))
OBJ_ASM		= $(addprefix $(OBJ_PATH)/, $(OBJ_ASM_NAME))

NB_ASM		= $(words $(ASM_CORE_NAME), $(ASM_CHECK_NAME), $(ASM_PARSE_NAME), $(ASM_TRANSLATE_NAME))
NB			= $(words $(SRC), $(NCURSES_SRC))
INDEX		= 0
INDEX_ASM	= 0

all : $(ASM_NAME) $(NAME)

$(NAME) : $(LIBFT) $(FT_PRINTF) $(OBJ) $(OBJ_NCURSES)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(OBJ_NCURSES) $(LIBFT) $(FT_PRINTF) $(NCURSES) $(SDL) $(SDL_MIXER) $(SDLINC)
	@printf "\r\033[32m [100%%] : CoreWar Ready ✓\033[0m\033[K\n"

$(ASM_NAME) : $(LIBFT) $(FT_PRINTF) $(ASM_OBJ_CORE) \
		$(ASM_OBJ_CHECK_PATH) $(ASM_OBJ_CHECK) $(ASM_OBJ_PARSE_PATH) \
		$(ASM_OBJ_PARSE) $(ASM_OBJ_TRANSLATE_PATH) $(ASM_OBJ_TRANSLATE)
	@$(CC) $(FLAGS) -o $(ASM_NAME) $(ASM_INCLUDES) $(ASM_OBJ_CORE) $(ASM_OBJ_CHECK) \
		$(ASM_OBJ_PARSE) $(ASM_OBJ_TRANSLATE) $(LIBFT) $(FT_PRINTF)
	@printf "\r\033[32m [100%%] : ASM Ready ✓\033[0m\033[K\n"

$(LIBFT) : 
	@make -C $(LIBFT_PATH) all
	@printf "\n LIBFT Compiled\n"

$(FT_PRINTF) :
	@make -C $(FT_PRINTF_PATH)
	@printf "\n FT_PRINTF Compiled\n"

$(OBJ_PATH) :
	@mkdir -p $@

$(ASM_OBJ_CORE_PATH) :
	@mkdir -p $@

$(ASM_OBJ_CHECK_PATH) :
	@mkdir -p $@

$(ASM_OBJ_PARSE_PATH) :
	@mkdir -p $@

$(ASM_OBJ_TRANSLATE_PATH) :
	@mkdir -p $@

$(ASM_OBJ_CORE_PATH)/%.o : $(ASM_PATH)/%.c $(ASM_HEADERS) Makefile | $(OBJ_PATH) $(ASM_OBJ_CORE_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX_ASM)*100/$(NB_ASM)))))
	@$(CC) $(FLAGS) -c $< $(ASM_INCLUDES) -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling ASM : $<"
	@$(eval INDEX_ASM=$(shell echo $$(($(INDEX_ASM)+1))))

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(COREWAR_HEADERS) Makefile | $(OBJ_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(FLAGS) -c $< -o $@ $(SDLINC)
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling Sources : $<"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_PATH)/%.o : $(NCURSES_SRC_PATH)/%.c $(COREWAR_HEADERS) Makefile | $(OBJ_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(CC) $(FLAGS) -c $< -o $@ $(SDLINC)
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling Sources : $<"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(ASM_OBJ_CHECK_PATH)/%.o : $(ASM_CHECK_PATH)/%.c $(ASM_HEADERS) Makefile | $(ASM_OBJ_CHECK_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX_ASM)*100/$(NB_ASM)))))
	@$(CC) $(FLAGS) -c $< $(ASM_INCLUDES) -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling ASM : $<"
	@$(eval INDEX_ASM=$(shell echo $$(($(INDEX_ASM)+1))))

$(ASM_OBJ_PARSE_PATH)/%.o : $(ASM_PARSE_PATH)/%.c $(ASM_HEADERS) Makefile | $(ASM_OBJ_PARSE_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX_ASM)*100/$(NB_ASM)))))
	@$(CC) $(FLAGS) -c $< $(ASM_INCLUDES) -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling ASM : $<"
	@$(eval INDEX_ASM=$(shell echo $$(($(INDEX_ASM)+1))))

$(ASM_OBJ_TRANSLATE_PATH)/%.o : $(ASM_TRANSLATE_PATH)/%.c $(ASM_HEADERS) Makefile | $(ASM_OBJ_TRANSLATE_PATH)
	$(eval PERCENT=$(shell echo $$(($(INDEX_ASM)*100/$(NB_ASM)))))
	@$(CC) $(FLAGS) -c $< $(ASM_INCLUDES) -o $@
	@printf "\r [%s%%] : %s" $(PERCENT) "Compiling ASM : $<"
	@$(eval INDEX_ASM=$(shell echo $$(($(INDEX_ASM)+1))))

clean :
	@make -C $(LIBFT_PATH) clean
	@make -C $(FT_PRINTF_PATH) clean
	@rm -rf $(ASM_OBJ_CORE) $(ASM_OBJ_CHECK) $(ASM_OBJ_PARSE) $(ASM_OBJ_TRANSLATE) $(OBJ_PATH)
	@printf "\r %s \033[32m✓\033[0m\n" "ASM Objects clean"
	@rm -rf $(OBJ) $(OBJ_PATH)
	@printf "\r %s \033[32m✓\033[0m\n" "CoreWar Objects clean"

fclean : clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(FT_PRINTF_PATH) fclean
	@rm -f $(ASM_NAME)
	@printf "\r %s \033[32m✓\033[0m\n" "ASM clean"
	@rm -f $(NAME)
	@printf "\r %s \033[32m✓\033[0m\n" "CoreWar clean"

#.NOTPARALLEL:
re : fclean all

norme : 
	norminette $(SRC) $(INC) $(LIBFT_PATH) $(FT_PRINTF_PATH)
	norminette $(INC) $(ASM_CORE) $(ASM_CHECK) $(ASM_PARSE) $(ASM_TRANSLATE) $(LIBFT_PATH) $(FT_PRINTF_PATH)

out : all
	#

debug : $(LIBFT) $(FT_PRINTF) $(OBJ) $(OBJ_PARSER) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(OBJ_PARSER) $(LIBFT) $(FT_PRINTF) -fsanitize=address

debug_g : $(LIBFT) $(FT_PRINTF) $(OBJ) $(OBJ_PARSER) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(OBJ_PARSER) $(LIBFT) $(FT_PRINTF) -g

sdl2_brew:
	brew install sdl2
	brew link sdl2
	brew install sdl2_mixer
	brew link sdl2_mixer

sdl2_ubuntu:
	sudo apt install libsdl2-2.0-0 libsdl2-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev
