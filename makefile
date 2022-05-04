CFLAGS= -g -Wall -Wextra -Wwrite-strings

Durak: main.cpp
	g++ ${CFLAGS} -o Durak main.cpp Card.cpp Deck.cpp
clean:
	rm -f Durak
