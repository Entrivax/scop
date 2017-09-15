# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/04 13:57:54 by lpilotto          #+#    #+#              #
#    Updated: 2017/09/04 14:54:42 by lpilotto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=scop
SRCDIR=src/
OBJDIR=obj/
INCDIR=./include
SRCFILES=main.c \
		binary_reader.c \
		build_shader_prog.c \
		destroy_app.c \
		exit_window.c \
		key_events.c \
		load_tex.c \
		loop.c \
		mat4_identity.c \
		mat4_mult.c \
		mat4_rotate.c \
		mat4_translate.c \
		parse_args.c \
		parse_obj.c \
		sec_malloc.c \
		start_app.c
OBJ=$(addprefix $(OBJDIR),$(subst .c,.o,$(SRCFILES)))
SRC=$(addprefix $(SRCFOLDER),$(SRCFILES))
LIBXDIR=./minilibx_macos
LIBX=$(LIBXDIR)/libmlx.a
LIBFTDIR=./libft
LIBFT=$(LIBFTDIR)/libft.a
LIBLISTDIR=./liblist
LIBLIST=$(LIBLISTDIR)/liblist.a
EFLAGS=-Wall -Werror -Wextra -g
IFLAGS=-I$(LIBFTDIR) -I$(LIBLISTDIR)/include -I$(INCDIR) -I$(LIBXDIR)
LFLAGS=-L$(LIBXDIR) -lmlx -framework OpenGL -framework AppKit \
		-L$(LIBFTDIR) -lft \
		-L$(LIBLISTDIR) -llist

.PHONY: all clean fclean re

$(NAME): $(LIBFT) $(LIBLIST) $(LIBX) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LFLAGS)

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if ! [ -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	gcc -c $< $(EFLAGS) $(IFLAGS) -o $@

$(LIBX):
	make -C $(LIBXDIR) all

$(LIBFT):
	make -C $(LIBFTDIR) all

$(LIBLIST):
	make -C $(LIBLISTDIR) all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(LIBLISTDIR) fclean
	make -C $(LIBXDIR) clean

re: fclean all
