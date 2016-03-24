EXEC	= avm

SRC		= main.cpp Exception.cpp VMFactory.cpp

RM		= rm -f

FLAGS   = -Wall -Wextra -Werror

all:	$(EXEC) 

$(EXEC):
		g++ -o $(EXEC) $(SRC) $(FLAGS)

clean:
		$(RM) $(EXEC)

re:		clean all