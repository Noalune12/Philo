CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -MMD -MP -g3

NAME = philo

RM = rm -f

OBJDIR = objs

SRCS = philo.c utils.c init.c threads.c utils_routine.c monitor.c utils_routine2.c
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
