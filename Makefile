# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/09/14 23:54:19 by vsporer          ###   ########.fr        #
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
				$(PATH_SRC)ft_ls_recursion.c

OBJ =			$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ..."
	@$(CC) $(INC) $^ -o $@
	@echo "Done !"

$(LIBFT):
	@echo "Compilig $@ ..."
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "Compiling $< to $@"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(NAME) and $(LIBFT) removed."

re: fclean all

test: all
	@echo "##########Start Test##########"
	@echo ""
	./$(NAME) Makefile %test
	@echo ""
	@echo "###########End Test###########"
