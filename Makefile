# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/09/18 15:19:52 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			ft_ls
LIBFT =			libft/libft.a

PATH_LIBFT =	libft/
PATH_SRC =		src/
PATH_OBJ =		objs/

CC =			gcc -Wall -Werror -Wextra
INC =			-I includes/ -I libft/includes/

SRC =			$(PATH_SRC)main.c\
				$(PATH_SRC)ft_ls_parser.c\
				$(PATH_SRC)ft_ls_error.c\
				$(PATH_SRC)ft_ls_tools.c\
				$(PATH_SRC)ft_ls_sort.c\
				$(PATH_SRC)ft_ls_display.c\
				$(PATH_SRC)ft_ls_display_file.c\
				$(PATH_SRC)ft_ls_get_dir.c\
				$(PATH_SRC)ft_ls_get_file.c\
				$(PATH_SRC)ft_ls_get_infolen.c\
				$(PATH_SRC)ft_ls_get_permission.c\
				$(PATH_SRC)ft_ls_del_struct.c\
				$(PATH_SRC)ft_ls_symdir.c\
				$(PATH_SRC)ft_ls_file_inline.c\
				$(PATH_SRC)ft_ls_color.c\
				$(PATH_SRC)ft_ls_get_time.c\
				$(PATH_SRC)ft_ls_sort_arg.c\
				$(PATH_SRC)ft_ls_get_path.c\
				$(PATH_SRC)ft_ls_recursion.c

OBJ =			$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ..."
	@$(CC) $(INC) $^ -o $@
	@echo "\033[32mDone !\033[0m"

$(LIBFT):
	@echo "Compilig $@ ..."
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "\033[35mCompiling $< to $@\033[0m"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "\033[31mObject files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[31m$(NAME) and $(LIBFT) removed.\033[0m"

.PHONY: clean fclean re

re: fclean all
