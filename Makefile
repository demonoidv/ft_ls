NAME = 			ft_ls
LIBFT =			libft/libft.a

PATH_LIBFT =	libft/
PATH_SRC =		src/
PATH_OBJ =		objs/

CC =			gcc -Wall -Werror -Wextra
INC =			-I includes/ -I libft/includes/

SRC =			$(PATH_SRC)main.c\
				$(PATH_SRC)ft_ls_parser.c\
				$(PATH_SRC)ft_ls_error.c

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
	@./$(NAME) -R
	@echo ""
	@echo "###########End Test###########"
