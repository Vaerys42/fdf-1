# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/17 12:03:20 by ycribier          #+#    #+#              #
#    Updated: 2013/12/22 20:20:21 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf
NAME_MINILIBX	=	mlx
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	./includes
DIR_LIBS		=	/usr/X11/lib
LDFLAGS			=	-L$(DIR_LIBS) -lXext -lX11 -lmlx
FLAGS			=	-Wall -Wextra -Werror
SRCS			=	main.c fdf.c draw_line.c vtx_table.c
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
