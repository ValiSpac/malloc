ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME        := libft_malloc_$(HOSTTYPE).so
LINK_NAME   := libft_malloc.so

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -Iinc -Ilibft -fPIC -g
LIBFT_DIR   := libft
LIBFT_LIB   := $(LIBFT_DIR)/libft.a
LDFLAGS     := -shared -L$(LIBFT_DIR)

SRCDIR      := src
OBJDIR      := obj
INCDIR      := inc
SRCS        := $(wildcard $(SRCDIR)/*.c)
OBJS        := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


TESTDIR     := test
TESTSRC     := $(TESTDIR)/main.c
TESTBIN     := $(TESTDIR)/test
TESTFLAGS   := -Wall -Wextra -Werror -Iinc -I$(LIBFT_DIR)

all: $(NAME) $(LINK_NAME)

$(NAME): libft $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) -L$(LIBFT_DIR) -lft


$(LINK_NAME): $(NAME)
	@ln -sf $< $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

test: $(TESTBIN)

$(TESTBIN): $(TESTSRC)
	@$(CC) $(TESTFLAGS) $< -o $@
run: all test
	@LD_PRELOAD=./$(LINK_NAME) ./$(TESTBIN)

valgrind: all test
	@LD_PRELOAD=./$(LINK_NAME) valgrind ./$(TESTBIN)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) $(LINK_NAME) $(TESTBIN)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libft test run
