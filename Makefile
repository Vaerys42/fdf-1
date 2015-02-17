# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/17 12:03:20 by ycribier          #+#    #+#              #
#    Updated: 2015/02/17 20:12:14 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
FLAGS			=	-g #-Wall -Wextra -Werror
NAME			=	fdf
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	-I $(LIB_PATH)./includes -I ./includes -I /usr/X11/include
DIR_LIBS		=	/usr/X11/lib
LDFLAGS			=	-L$(DIR_LIBS) -lXext -lX11 -lmlx
SRCS			=	srcs/main.c								\
					srcs/parser.c							\
					srcs/color_convert.c					\
					srcs/color_gradient.c					\
					srcs/color_calc.c						\
					srcs/draw_line.c						\
					srcs/mlx_handler.c						\
					srcs/hook.c								\
					srcs/keys.c								\
					srcs/vtx_table.c
OBJS			=	$(SRCS:srcs/%.c=objs/%.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ $(LDFLAGS) -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LIB):
	@make -C $(LIB_PATH)

obj:
	@mkdir -p objs

objs/%.o: srcs/%.c ./includes/fdf.h
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@rm -rf objs
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: clean all re fclean

