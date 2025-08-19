# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 19:20:28 by nchairun          #+#    #+#              #
#    Updated: 2025/08/19 19:32:53 by nchairun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= cc
CFLAGS		= -Werror -Wall -Wextra -pthread


SRCS_DIR	= src
SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/parsing/parse_table.c

BUILD_DIR	= build
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/src/%.o)

all: $(NAME)

.SILENT:

$(BUILD_DIR)/src/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I include/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
