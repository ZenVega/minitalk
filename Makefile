# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 10:42:30 by uschmidt          #+#    #+#              #
#    Updated: 2025/01/23 15:17:00 by uschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_FILES = \
server.c\

CLIENT_FILES = \
client.c\

SERVER_FILES_BONUS = \
server_bonus.c\

CLIENT_FILES_BONUS = \
client_bonus.c\

SERVER_OFILES = $(SERVER_FILES:.c=.o)
CLIENT_OFILES = $(CLIENT_FILES:.c=.o)

SERVER_OFILES_BONUS = $(SERVER_FILES_BONUS:.c=.o)
CLIENT_OFILES_BONUS = $(CLIENT_FILES_BONUS:.c=.o)

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SERVER = server
CLIENT = client
 
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(SERVER) $(CLIENT)

bonus: $(SERVER)_bonus $(CLIENT)_bonus

$(SERVER): $(SERVER_OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OFILES) $(LIBFT) -no-pie

$(CLIENT): $(CLIENT_OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OFILES) $(LIBFT) -no-pie

$(SERVER)_bonus: $(SERVER_OFILES_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER)_bonus $(SERVER_OFILES_BONUS) $(LIBFT) -no-pie

$(CLIENT)_bonus: $(CLIENT_OFILES_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT)_bonus $(CLIENT_OFILES_BONUS) $(LIBFT) -no-pie

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

test_5:
	./client $(PID) "AAAAA" & ./client $(PID) "BBBB" & ./client $(PID) "CCC"

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm $(SERVER) $(CLIENT) $(SERVER)_bonus $(CLIENT)_bonus

re: fclean all

.PHONY: all clean fclean re
