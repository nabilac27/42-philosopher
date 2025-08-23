# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 19:20:28 by nchairun          #+#    #+#              #
#    Updated: 2025/08/23 15:24:09 by nchairun         ###   ########.fr        #
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
SRCS		= $(SRCS_DIR)/main.c 							\
			  $(SRCS_DIR)/01-parse/clean.c					\
			  $(SRCS_DIR)/01-parse/parse.c					\
			  $(SRCS_DIR)/02-init/handle_mutex.c			\
			  $(SRCS_DIR)/02-init/init_philo_struct.c		\
			  $(SRCS_DIR)/02-init/init_table_struct.c		\
			  $(SRCS_DIR)/03-threads/threads.c				\
			  $(SRCS_DIR)/04-routines/monitor_routine.c		\
			  $(SRCS_DIR)/04-routines/philo_routine.c		\
			  $(SRCS_DIR)/04-routines/philo_routine_utils.c	\
			  $(SRCS_DIR)/04-routines/time_utils.c			\

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
