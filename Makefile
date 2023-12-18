CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = server

SRC = main.cpp server.cpp parse.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CPP) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)
re: clean all

.PHONY: clean all re
