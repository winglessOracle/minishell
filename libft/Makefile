# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/05/15 17:30:41 by ccaljouw      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m

NAME		= libft.a
CC			?= clang
AR			= ar -rsc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
OBJ_FILES	=		$(addprefix obj/, ft_free.o ft_free_array.o ft_strchr.o ft_strdup.o\
						ft_strlen.o ft_strlcpy.o ft_strcmp.o  ft_strcmp_case.o ft_substr.o ft_calloc.o \
						ft_bzero.o ft_memset.o ft_memcpy.o ft_strjoin.o ft_strncmp.o ft_strjoin_free_s1.o \
						ft_split.o ft_itoa.o ft_toupper.o ft_tolower.o \
						ft_putstr_fd.o ft_freearr.o ft_isalpha.o ft_atoi_long.o ft_isdigit.o ft_isspace.o)

OBJ_PRINTF = 		$(addprefix obj_printf/, ft_printf.o ft_sprintf.o ft_printf_format.o ft_printf_set.o \
						ft_printf_getargs.o ft_itoa_printf.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(OBJ_PRINTF)
	@$(AR) $(NAME) $(OBJ_FILES) $(OBJ_PRINTF)

$(OBJ_FILES): obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_PRINTF): obj_printf/%.o: ft_printf/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@echo "$(BLUE)Cleaning libft$(RESET)"
	@$(RM) obj/
	@$(RM) obj_printf/

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re