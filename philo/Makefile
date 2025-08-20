# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 19:20:28 by nchairun          #+#    #+#              #
#    Updated: 2025/08/20 04:22:19 by nchairun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################
##				PROGRAM NAME, COMPILE FLAGS		 			 ##
###############################################################

NAME		= philo
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -pthread -I include


###############################################################
##						DIRECTORIES				 			 ##
###############################################################

SRCS_DIR	= src
SRCS		= $(SRCS_DIR)/main.c 						\
			  $(SRCS_DIR)/01-parsing/parse_table.c		\
			  $(SRCS_DIR)/02-init_table/init_table.c	\
			  $(SRCS_DIR)/02-init_table/handle_mutex.c	\
			  $(SRCS_DIR)/03-exec_dinner/exec_dinner.c	\
			  $(SRCS_DIR)/03-exec_dinner/synchro_philos.c

BUILD_DIR	= build
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/src/%.o)

################################################################
##                          RULES                             ##
################################################################
all: $(NAME)

.SILENT:

# Compile object files
$(BUILD_DIR)/src/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I include/

# Link the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Remove object files
clean:
	rm -rf $(BUILD_DIR)

# Remove executable and object files
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all re clean fclean
