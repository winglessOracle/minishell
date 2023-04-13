# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: carlo <carlo@student.42.fr>                  +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 09:28:26 by cwesseli      #+#    #+#                  #
#    Updated: 2023/04/13 15:15:18 by ccaljouw      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RESET	:= \033[0m

NAME		= libft.a
CC			= clang
AR			= ar -rsc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
OBJ_FILES	=		$(addprefix obj/, ft_free.o ft_free_array.o ft_strchr.o ft_strdup.o\
						ft_strlen.o ft_strlcpy.o ft_strcmp.o ft_substr.o ft_calloc.o ft_bzero.o \
						ft_memset.o ft_strjoin.o ft_strncmp.o ft_strjoin_free_s1.o ft_split.o ft_freearr.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $(NAME) $(OBJ_FILES)

$(OBJ_FILES): obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)$(BOLD)Compiling:$(RESET) $(notdir $<)"
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@echo "$(BLUE)Cleaning libft$(RESET)"
	@$(RM) obj/

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re