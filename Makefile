# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 16:13:31 by ypacileo          #+#    #+#              #
#    Updated: 2025/05/10 19:42:12 by yuliano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Flags para compilación normal y depuración
CFLAGS = -Wall -Wextra -Werror -fPIC -g -O0

SRC = main.c thread_init.c thread_states.c tools.c
OBJ = $(SRC:.c=.o)

# Regla principal
all: $(NAME)

# Regla para compilar el ejecutable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

# Regla para limpiar los archivos objeto
clean:
	rm -f $(OBJ)

# Regla para limpiar todo, incluyendo el ejecutable
fclean: clean
	rm -f $(NAME)

# Regla para recompilar desde cero
re: fclean all

# Declaración de reglas que no son archivos
.PHONY: all clean fclean re
