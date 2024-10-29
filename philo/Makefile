PRE = ./
INCLUDE = $(PRE)Include
# BONUS = ./philo_bonus/
# INCLUDE_BONUS = $(BONUS)Include

SOURCE = main.c errors.c philo.c utils.c lst_op.c time_utils.c state.c \
		 watcher_utils.c death_utils.c

# SOURCE_BON = 

SOURCES = ${addprefix $(PRE), $(SOURCE)}
# SOURCES_BON = ${addprefix $(PRE), $(SOURCE_BON)}

NAME = philo
# NAME_BONUS = philo_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread
# -fsanitize=thread

OBJ = $(SOURCES:.c=.o)
# OBJ_BON = $(SOURCES_BON:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) -o $@ $^

.c.o:
		$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

# bonus: $(NAME_BONUS)

# $(NAME_BONUS): $(OBJ_BON)
# 	cc $(FLAGS) -o $@ $^

# .c.o2:
# 	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

clean: 
	rm -f $(OBJ)
        
fclean: clean
	rm -f $(NAME)

re: fclean all
