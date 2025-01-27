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

SERVER_OFILES = $(SERVER_FILES:.c=.o)
CLIENT_OFILES = $(CLIENT_FILES:.c=.o)

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SERVER = server
CLIENT = client
 
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OFILES) $(LIBFT) -no-pie

$(CLIENT): $(CLIENT_OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OFILES) $(LIBFT) -no-pie

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	$(MAKE) clean
	rm $(SERVER) $(CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
