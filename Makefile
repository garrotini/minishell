NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I src
LDFLAGS = -lreadline

OBJ_DIR = obj
SRC_DIR = src

SRCS = src/main.c \
       src/init/init_shell.c \
       src/init/signals.c \
       src/init/signals_heredoc.c \
       src/lexer/lexer.c \
       src/lexer/split.c \
       src/lexer/split_utils.c \
       src/lexer/token.c \
       src/lexer/var_expansion.c \
       src/lexer/var_expansion_utils.c \
       src/lexer/var_split.c \
       src/lexer/var_split_utils.c \
       src/lexer/var_split_utils2.c \
       src/lexer/rm_quote.c \
       src/lexer/rm_quote_utils.c \
       src/lexer/syntaxer.c \
       src/parser/parser.c \
       src/parser/parse_word.c \
       src/parser/parse_word_utils.c \
       src/parser/parse_pipe.c \
       src/parser/parse_semicolon.c \
       src/parser/parse_input.c \
       src/parser/parse_output.c \
       src/parser/parse_heredoc.c \
       src/parser/parse_heredoc_utils.c \
       src/parser/parse_heredoc_expand.c \
       src/execution/executor.c \
       src/execution/exec_utils.c \
       src/execution/exec_utils_2.c \
       src/execution/exec_builtin_utils.c \
       src/execution/exec_pipeline.c \
       src/builtins/builtins.c \
       src/builtins/echo.c \
       src/builtins/cd.c \
       src/builtins/pwd.c \
       src/builtins/env.c \
       src/builtins/export.c \
       src/builtins/unset.c \
       src/builtins/exit.c \
       src/exit/exit_clean.c \
			 src/exit/exit_clean_utils.c \
       src/exit/error.c \
       src/utils/tk_utils.c \
       src/utils/cmd_utils1.c \
       src/utils/cmd_utils2.c \
       src/utils/env_utils.c \
       src/utils/env_utils2.c \
       src/utils/str_utils1.c \
       src/utils/str_utils2.c \
       src/utils/str_utils3.c \
       src/utils/utils1.c \
       src/utils/utils2.c \
       src/utils/utils3.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# valgrind_full
vf: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

# valgrind_suppressed
vs: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re vf vs

