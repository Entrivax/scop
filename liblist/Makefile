
NAME=liblist.a
SRCDIR=src/
OBJDIR=obj/
INCDIR=./include
SRCFILES=list_add.c \
		list_clear.c \
		list_delete_at.c \
		list_destroy.c \
		list_free_all.c \
		list_new.c \
		list_pop_at.c
OBJ=$(addprefix $(OBJDIR),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
LIBFTDIR=../libft
LIBFT=$(LIBFTDIR)/libft.a
IFLAGS=-I$(LIBFTDIR) -I$(INCDIR)
FLAGS=-Wall -Werror -Wextra

.PHONY: all clean fclean re

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if ! [ -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	gcc -c $(FLAGS) $(IFLAGS) $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR) all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all