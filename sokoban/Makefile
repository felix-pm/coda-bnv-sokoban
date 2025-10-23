# Makefile

NAME = 	exe_sokoban

SRCS = 	main.c \
		grid.c \
		win.c \
		fonctions.c
		

all :	$(NAME)

$(NAME):	$(SRCS)
	\gcc $(SRCS) -o $(NAME)

fclean:
	\rm -f $(NAME)

re: fclean all
