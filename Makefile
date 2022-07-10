NAME		=	ircserv

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -MMD

ifeq ($(D), 3)
	CXXFLAGS += -D DEBUG=2
else ifeq ($(D), 2)
    CXXFLAGS += -fsanitize=address -D DEBUG=2
else ifeq ($(D), 1)
    CXXFLAGS += -fsanitize=address    
endif

SRC			=	srcs/main.cpp \
				srcs/socket.cpp \
				srcs/User.cpp \
				srcs/Server/Server.cpp \
				srcs/Server/ServerGetters.cpp \
				srcs/Server/ServerParser.cpp \
				srcs/Server/ServerUtils.cpp \
				srcs/Server/ServerChannel.cpp \
				srcs/Commands.cpp \
				srcs/MessageBuilder.cpp \
				srcs/Commands/cap.cpp \
				srcs/Commands/nick.cpp \
				srcs/Commands/oper.cpp \
				srcs/Commands/pass.cpp \
				srcs/Commands/ping.cpp \
				srcs/Commands/user.cpp \
				srcs/Commands/usermode.cpp \
				srcs/Commands/channelmode.cpp \
				srcs/Commands/whois.cpp \
				srcs/Commands/join.cpp \
				srcs/Commands/part.cpp \
				srcs/Commands/names.cpp \
				srcs/Commands/quit.cpp \
				srcs/Commands/error.cpp \
				srcs/Commands/kill.cpp \
				srcs/Commands/invite.cpp \
				srcs/Commands/privateMessage.cpp \
				srcs/Commands/kick.cpp \
				srcs/Commands/topic.cpp \
				srcs/Commands/list.cpp \
				srcs/Channel.cpp

DEP			=	$(SRC:.cpp=.d)

OBJ			=	$(DEP:.d=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)


%.o: 		%.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ)
			rm -rf $(DEP)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

run:
			make all && ./$(NAME)

-include $(DEP)

.PHONY:		all clean fclean re
