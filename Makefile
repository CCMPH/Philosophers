# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: chartema <chartema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/07 10:59:05 by chartema      #+#    #+#                  #
#    Updated: 2022/09/07 14:33:30 by chartema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
#-g -fsanitize=address
#-g -fsanitize=thread

INC = -I ./include

SRC_FILES = main.c check_input.c error.c initialize.c utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJS = $(addprefix obj/, $(OBJ_FILES))

HEADERFILES = include/philosophers.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADERFILES)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)
	@echo "Creating executable"

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

norm:
	norminette include/ src/
	@echo "Check of files are norm proof"

clean:
	$(RM) ./obj
	@echo "Removing object files"

fclean: clean
	$(RM) $(NAME)
	@echo "Removing executable file"

re: fclean all

.PHONY: all, clean, fclean, re