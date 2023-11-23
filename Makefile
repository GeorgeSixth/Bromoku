NAME 	= 	Gomoku

SRC 	= 	./sources/Arbiter.cpp	\
		./sources/Game.cpp	\
		./sources/Map.cpp	\
		./sources/Player.cpp	\
		./sources/Menu.cpp	\
		./sources/IA.cpp	\
		./sources/Render.cpp	\
		./sources/main.cpp


LIB += -L/usr/local/lib
LIB += /usr/local/lib/libsfml-graphics.so.1.6
LIB += /usr/local/lib/libsfml-window.so.1.6
LIB += /usr/local/lib/libsfml-system.so.1.6
LIB += /usr/local/lib/libsfml-audio.so.1.6

CXX 	+=	-I./include -I/usr/local/include/SFML/
OBJS 	=	$(SRC:.cpp=.o)

CC	= 	g++

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIB)

all:		$(NAME)

clean:
		@rm -f $(OBJS)
		@rm -rf *~

fclean:		clean
		@rm -rf $(NAME)

re:		fclean all

run:        $(NAME)
            

.PHONY:		all clean fclean re
