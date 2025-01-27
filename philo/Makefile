# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 08:40:49 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/27 08:43:28 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -MMD -MP -g3

NAME = philo

RM = rm -f

OBJDIR = objs

SRCS = philo.c utils.c init_philos.c init_simu.c threads.c philo_routine.c eat_routine.c utils_routine.c monitor.c
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "💫✨💫 \033[92mPhilo compiled\033[0m 💫✨💫"

$(OBJDIR)/%.o : %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) -rf $(OBJDIR)

fclean : clean
	$(RM) $(NAME)
	@echo "🧹🧹🧹 \033[92mCleaning philo complete\033[0m 🧹🧹🧹"

re : fclean all

.PHONY : all clean fclean re

-include $(DEPS)
