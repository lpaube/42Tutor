NAME =		rush-02

SRCS_DIR =	srcs
INCLS_DIR =	incls
OBJS_DIR =	objs

SRCS =		main.c read_dict.c utils.c

OBJS =		$(SRCS:.c=.o)

SRCS_FULL = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS_FULL =	$(addprefix $(OBJS_DIR)/, $(OBJS))

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra -c

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo Created: Object directory

$(NAME): $(OBJS_FULL)
	@$(CC) $(OBJS_FULL) -o $(NAME)
	@echo "\\n\033[32;1m RUSH02 HAS BEEN GENERATED \033[0m \\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "Created: $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf $(OBJS_FULL) $(OBJS_DIR)
	@echo "\033[34;1m CLEANED OBJECT FILES \033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[34;1m CLEANED RUSH02 \033[0m"

re: fclean all

.PHONY: all clean fclean re
