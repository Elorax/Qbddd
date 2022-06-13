SRCS		=	main.c								\
				gnl/get_next_line.c					\
				gnl/get_next_line_utils.c			\
				src/map/check_args.c				\
				src/map/check_line.c				\
				src/map/data.c						\
				src/map/formatting_line.c			\
				src/map/read_line.c					\
				src/map/read_map.c					\
				src/map/split.c						\
				src/map/utils.c						\
				src/init_images.c					\
				src/key_hook.c						\
				src/test_get_addr.c					\
				src/build_image.c					\
				src/init_raycasting.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	Cube3d

%.o: %.c
			$(CC) $(CFLAGS) -I /usr/include -Imlx_linux -c $< -o $@


LINUX		= -I /usr/include -L /usr/lib -L mlx_linux -I mlx_linux -lXext -l X11 -lm -lz

$(NAME):		$(OBJS)
					make -C minilibx/
					make -C libft/
					$(CC) $(CFLAGS) $(OBJS) minilibx/libmlx_Linux.a libft/libft.a $(LINUX) -o $(NAME)

				

all:			$(NAME)

clean:
				rm -rf $(OBJS)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
