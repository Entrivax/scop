
NAME=unit_tests
SRCDIR=./
OBJDIR=./
INCDIR=.
SRCFILES=main.c \
		unit.c
OBJ=$(addprefix $(OBJDIR),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
LIBLISTDIR=..
LIBLIST=$(LIBLISTDIR)/liblist.a
IFLAGS=-I$(LIBLISTDIR)/include -I../../libft -I$(INCDIR)
FLAGS=-Wall -Werror -Wextra
LFLAGS=-L../../libft -lft -L$(LIBLISTDIR) -llist

.PHONY: all clean fclean re run

$(NAME): $(OBJ)
	gcc -o $(NAME) $(LFLAGS) $(OBJ) $(LFLAGS)

run: $(NAME)
	./$(NAME)

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if ! [ -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	gcc -c $(FLAGS) $(IFLAGS) $< -o $@

$(LIBLIST):
	make -C $(LIBLISTDIR) all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all