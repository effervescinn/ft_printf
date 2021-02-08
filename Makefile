FILES = lib_fts.c ft_printf.c parser.c write_d.c write_d_utils.c write_s.c write_perc.c write_u.c write_u_utils.c write_x.c write_x_utils.c write_p.c write_c.c
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