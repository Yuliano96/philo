# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 16:13:31 by ypacileo          #+#    #+#              #
#    Updated: 2025/05/22 22:47:28 by yuliano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_DIR = ./src
OBJ_DIR = ./obj
CFLAGS = -Wall -Wextra -Werror  -I./ -fPIC -g -O0

SRC = main.c thread_init.c thread_states.c tools.c aux_thread_init.c \
    death_monitor.c meals_monitor.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo "✅ ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "✅ total cleaning"

re: fclean all

.PHONY: all clean fclean re
