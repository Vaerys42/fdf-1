# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/17 12:03:20 by ycribier          #+#    #+#              #
#    Updated: 2015/02/11 15:59:10 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf
NAME_MINILIBX	=	mlx
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	./includes
DIR_LIBS		=	/usr/X11/lib
LDFLAGS			=	-L$(DIR_LIBS) -lXext -lX11 -lmlx
FLAGS			=	#-g -Wall -Wextra -Werror
SRCS			=	main.c								\
					fdf.c								\
					color_convert.c						\
					color_gradient.c					\
					color_calc.c						\
					draw_line.c							\
					vtx_table.c
OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	gcc $(FLAGS) -o $@ $^ $(LDFLAGS) -L $(LIB_PATH) -lft

$(LIB):
	make -C $(LIB_PATH)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $^ -I $(LIB_PATH)$(INCLUDES) -I $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C $(LIB_PATH) fclean

re: fclean all

.PHONY: clean all re fclean
