NAME = minishell
SRC = \
   src/builtins/ft_cd1.c \
   src/builtins/ft_cd2.c \
   src/builtins/ft_echo.c \
   src/builtins/ft_env.c \
   src/builtins/ft_export1.c \
   src/builtins/ft_export2.c \
   src/builtins/ft_pwd.c \
   src/builtins/ft_exit.c \
   src/builtins/ft_unset.c \
   src/utils/utils1.c \
   src/utils/utils2.c \
   src/utils/utils3.c \
   src/utils/free.c \
   src/signals/signals.c \
   src/signals/heredoc_signals.c \
   src/execution/redirections1.c \
   src/execution/redirections2.c \
   src/execution/exec_pipes.c \
   src/execution/execution.c \
   src/execution/child_process.c \
   src/execution/exec_builtins.c \
   src/execution/find_cmd.c \
   src/execution/here_doc1.c \
   src/execution/here_doc2.c \
   src/execution/here_doc3.c \
   src/environment/env.c \
   src/environment/list_environment.c \
   src/environment/free_environment.c \
   src/lexer/lexer.c \
   src/lexer/free_lexer.c \
   src/lexer/lexer_list.c \
   src/lexer/double_quotes_handler.c \
   src/lexer/single_quotes_handler.c \
   src/lexer/parameter_handler.c \
   src/lexer/operator_handler.c \
   src/lexer/variable_handler.c \
   src/lexer/lexer_utils.c \
   src/parser/parser.c \
   src/parser/free_cmd.c \
   src/parser/create_cmd.c \
   src/parser/parser_utils.c \
   src/parser/fill_redirections.c \
   src/parser/fill_argv.c \
   src/parser/syntax_validation.c \
   src/run_shell.c \
   src/main.c

OBJ := $(SRC:%.c=obj/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -lreadline -lncurses -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

debug: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -fsanitize=address -g $^ -lreadline -lncurses -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj/
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug