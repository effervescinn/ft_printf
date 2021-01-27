FILES = ft_printf.c
OFILES = $(patsubst %.c,%.o,$(FILES))
HEADER = ft_printf.h
NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OFILES)
			ar rcs $(NAME) $(OFILES)
			
%.o:		%.c $(HEADER)
			gcc $(FLAGS) -c $< -o $@

clean:
			rm -f $(OFILES)

fclean:		clean
			rm -f $(NAME) 

re:			fclean all

.PHONY:		all clean fclean re