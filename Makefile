# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/05/09 09:45:07 by cwesseli      ########   odam.nl          #
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
OBJ_FILES	=  $(addprefix obj/src/, minishell.o lst_utils/t_node.o utils/utils.o lst_utils/t_smpl_cmd.o \
				lexer.o utils/env_utils.o init.o print.o lst_utils/node.o signals.o \
				lst_utils/delete.o lst_utils/t_pipe.o ) \
				$(addprefix obj/src/parser/, parser.o parser_utils.o parse_redirect.o quotes.o cond_pipe.o cond_pipe_utils.o check_syntax.o ) \
				$(addprefix obj/src/expander/, expander.o expand_var_utils.o wildcards.o ) \
				$(addprefix obj/src/executor/, executor.o executor_utils.o executor_utils2.o ) \

OBJ_BUILTIN = $(addprefix obj_buitin/, echo.o cd.o cd_utils.o cd_utils2.o pwd.o unset.o export.o env.o exit.o)

#//= Modifiable =//#
all: libft $(NAME)
	
$(NAME): libft $(OBJ_FILES) $(OBJ_BUILTIN)
	@$(CC) $(OBJ_FILES) $(OBJ_BUILTIN) $(LIBS) $(HEADERS) -o $(NAME) $(CFLAGS) -lreadline

bonus: CFLAGS = -Wall -Wextra -Werror -DBONUS=1
bonus: fclean all	

libft:
	@$(MAKE) -C $(LIBFT)

$(OBJ_FILES): obj/%.o: %.c 
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
	@echo "$(BLUE)Cleaning tester $(RESET)"
	@echo "$(BLUE)Cleaning history $(RESET)"
	@rm -rf tester/output
	@rm -rf tester/trace
	@rm -rf $(NAME_BONUS)
	@echo "" > log/history_log
	@$(MAKE) -C $(LIBFT) fclean

debug: CFLAGS = -Wall -Wextra
debug: all

re: fclean all

.PHONY:	all bonus clean fclean re libft debug
