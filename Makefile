# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/03/31 12:32:11 by cwesseli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m

#//= Variables = //#
NAME		= minishell
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g -lreadline

#//= Locations =//#
INCLUDE		= ./include
LIBFT		= ./libft
LIBS		= $(LIBFT)/libft.a 
HEADERS		= -I $(LIBFT) -I$(INCLUDE)
OBJ_FILES	= $(addprefix obj/, minishell.o list_utils.o parser.o utils.o lexer.o env.o init.o test.o\
				signals.o)

#//= Modifiable =//#
all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)
	
$(NAME): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) $(LIBS) $(HEADERS) -o $(NAME) $(CFLAGS) -lreadline

$(OBJ_FILES): obj/%.o: src/%.c 
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling minishell:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $< 

debug: CFLAGS = -Wall -Wextra
debug: all

clean:
	@echo "$(BLUE)Cleaning minishell$(RESET)"
	@rm -rf obj/
	@$(MAKE) -C $(LIBFT) clean
	
fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

debug: CFLAGS = -Wall -Wextra
debug: all

re:
	@$(MAKE) fclean
	@$(MAKE) all
	
.PHONY:	all clean fclean re libft debug
