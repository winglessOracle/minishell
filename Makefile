# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/05/02 19:34:28 by cariencaljo   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m

#//= Variables = //#
NAME		 = minishell
NAME_BONUS	 = minishell_bonus
CC			 = clang
CFLAGS		 = -Wall -Wextra -Werror

ifeq ($(USER), cariencaljouw)
	RL_INC			= /opt/homebrew/opt/readline/include
	RL_LIB			= /opt/homebrew/opt/readline/lib
else
	RL_INC		= /Users/$(USER)/.brew/opt/readline/include
	RL_LIB		= /Users/$(USER)/.brew/opt/readline/lib
endif

#//= Locations =//#
INCLUDE		= ./include
LIBFT		= ./libft
LIBS		= $(LIBFT)/libft.a -L$(RL_LIB)
HEADERS		= -I $(LIBFT) -I$(INCLUDE) -I$(RL_INC)
OBJ_FILES	= $(addprefix obj/, minishell.o lst_utils/t_node.o parser.o utils/utils.o lst_utils/t_smpl_cmd.o \
				lexer.o utils/env_utils.o init.o print.o lst_utils/node.o utils/parser_utils.o \
				utils/redirect_utils.o utils/quote_utils.o expander.o signals.o termios.o \
				lst_utils/delete.o executor.o utils/executor_utils.o utils/wildcards.o utils/cond_pipe.o \
				utils/cond_pipe_utils.o utils/check_syntax_utils.o lst_utils/t_pipe.o utils/expand_var_utils.o)

OBJ_BUILTIN = $(addprefix obj_buitin/, echo.o cd.o cd_utils.o pwd.o unset.o export.o env.o exit.o)

#//= Modifiable =//#
all: libft $(NAME)
	
$(NAME): libft $(OBJ_FILES) $(OBJ_BUILTIN)
	@$(CC) $(OBJ_FILES) $(OBJ_BUILTIN) $(LIBS) $(HEADERS) -o $(NAME) $(CFLAGS) -lreadline

bonus: CFLAGS = -Wall -Wextra -Werror -DBONUS=1
bonus: fclean all	

libft:
	@$(MAKE) -C $(LIBFT)

$(OBJ_FILES): obj/%.o: src/%.c 
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling minishell:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $< 

$(OBJ_BUILTIN): obj_buitin/%.o: builtin/%.c 
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling minishell builtins:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $< 

clean:
	@echo "$(BLUE)Cleaning minishell$(RESET)"
	@rm -rf obj/
	@rm -rf obj_buitin/
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@rm -rf ./tester/output
	@rm -rf ./tester/trace
	@$(MAKE) -C $(LIBFT) fclean

debug: CFLAGS = -Wall -Wextra
debug: all

re: fclean all

.PHONY:	all bonus clean fclean re libft debug
