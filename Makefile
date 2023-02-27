CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic-errors -g
SRC_V_FILES= main_v.cpp
OBJ_V=$(SRC_V_FILES:.cpp=.o)
NAME_V=main_v

SRC_M_FILES= main_m.cpp
OBJ_M=$(SRC_M_FILES:.cpp=.o)
NAME_M=main_m

all: $(NAME_V) $(NAME_M)

$(NAME_V): $(OBJ_V)
	$(CC) $(FLAGS) $(OBJ_V) -o $(NAME_V)

$(NAME_M): $(OBJ_M)
	$(CC) $(FLAGS) $(OBJ_M) -o $(NAME_M)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_V)
	rm -rf $(OBJ_M)

fclean: clean
	rm -rf $(NAME_V)
	rm -rf $(NAME_M)

re: fclean all

.PHONY: all clean fclean re
