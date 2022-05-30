SRCS		=	main.c								\
				src/map/check_args.c				\
				src/map/check_line.c				\
				src/map/data.c						\
				src/map/formatting_line.c			\
				src/map/read_line.c					\
				src/map/read_map.c					\
				src/map/split.c						\
				src/map/utils.c						\
				gnl/get_next_line.c					\
				gnl/get_next_line_utils.c			\

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	Cube3d

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@


$(NAME):		$(OBJS)
					make -C libft/
					$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

				

all:			$(NAME)


clean:
				rm -rf $(OBJS)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
