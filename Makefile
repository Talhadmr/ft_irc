CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = server

SRC = main.cpp server.cpp parse.cpp command.cpp Client.cpp Channel.cpp ./commands/Ping.cpp ./commands/Join.cpp ./commands/Pass.cpp ./commands/Nick.cpp ./commands/Who.cpp ./commands/Mode.cpp ./commands/Cap.cpp ./commands/Part.cpp ./commands/Topic.cpp ./commands/Privmsg.cpp ./commands/User.cpp

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
