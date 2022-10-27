
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <zweng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 12:41:50 by zweng             #+#    #+#              #
#    Updated: 2022/10/27 12:49:27 by vagrant          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE), )
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
# ----- varaibles -----

CC			= gcc

NAME		= libft_malloc_$(HOSTTYPE).so

LIB_NAME	= libft_malloc.so

LIB_PATH	= srcs/lib

HEADER_PATH	= includes

C_PATH 		= srcs

# ---------------- transformation ------------------ #

HEADER		= $(HEADER_PATH)/malloc.h 

CFILES		= $(notdir $(foreach D, $(C_PATH), $(wildcard $(D)/*.c)))
LIBFILES	= $(notdir $(foreach D, $(LIB_PATH), $(wildcard $(D)/*.c)))

OBJS_NAME	= $(patsubst %.c, %.o, $(CFILES)) \
	     	  $(patsubst %.c, %.o, $(LIBFILES))
DFILES_NAME	= $(patsubst %.c, %.d, $(CFILES)) \
			  $(patsubst %.c, %.d, $(LIBFILES))

OBJ_PATH	= obj
DPFLAGS		= -MD -MP
CFLAGS		= -Wall -Wextra -Werror -fPIC \
			  $(foreach D, $(HEADER_PATH), -I$(D)) $(DPFLAGS)

SFLAGE		= -shared

# ----- part automatic -----
SRCS = $(addprefix $(C_PATH)/,$(CFILES)) \
	   $(addprefix $(LIB_PATH)/,$(LIBFILES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJS_NAME))
DFLS = $(addprefix $(OBJ_PATH)/,$(DFILES_NAME))

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ----- Colors -----
# ==================

# ----- part rules -----
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(SFLAGE) $(OBJS) -o $@
	@rm -f $(LIB_NAME)
	@ln -s $(NAME) $(LIB_NAME)
	@printf $(GREEN)"$(NAME) Finish linking\n"$(EOC)

$(OBJ_PATH)/%.o:$(C_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o:$(LIB_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null

clean: 
	@rm -f $(OBJS) $(DFLS)
	@rm -rf $(OBJ_PATH) 2> /dev/null
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)

fclean: clean
	@/bin/rm -f $(NAME) $(LIB_NAME)
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)

-include $(DFLS)

re: fclean all

norme:
	@norminette $(SRCS)
	@norminette $(HEADER_PATH)/*.h

.PHONY: clean dclean fclean re norme all
