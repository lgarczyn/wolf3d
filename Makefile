# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2016/04/09 18:26:34 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC =	wolf3d.c arguments.c errors.c string.c\
		hooks.c inputs.c\
		render.c display.c casting.c column.c \
		map.c get_next_line.c memalloc.c

OBJ = $(SRC:.c=.o)

FLG = 

LIB =	-I minilibx_macos \
		-lmlx \
		-framework OpenGL -framework AppKit \
		-lpthread \

DEB = -g

OPT = -O3 -ffast-math

all: $(NAME)

libft:

$(NAME):$(OBJ)
	gcc $(FLG) $(OPT) $(OBJ) $(LIB) $(DEB) -o $(NAME)

%.o: %.c
	gcc $(FLG) $(OPT) $(DEB) -c $< $  -pthread

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

optire: fclean opti
