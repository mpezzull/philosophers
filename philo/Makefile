# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 17:56:09 by mde-rosa          #+#    #+#              #
#    Updated: 2021/10/05 20:04:50 by mde-rosa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	philo

SRCS		=	philo.c philo_utils.c philo_utils_2.c philo_routines.c

FLAGS		=	-Wall -Werror -Wextra -pthread

CC			=	gcc

OBJCS		=	$(SRCS:.c=.o)

.c.o		:
				@$(CC) $(FLAGS) -c $<

all			:	$(NAME)
			
$(NAME)		:	$(OBJCS)
				@$(CC) $(FLAGS) -o $(NAME) $(OBJCS)
			 	@echo "\033[1;32m$@ successfully build\033[0m"

clean		:
				@rm -f $(OBJCS)
			 	@echo "\033[1;31m.o files deleted\033[0m"

fclean		:	clean
				@rm -f $(NAME)
			 	@echo "\033[1;31mbinaries deleted\033[0m"

re			:	fclean all

.PHONY		:	all clean fclean re