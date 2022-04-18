CFLAGS= -g -Wall -Wextra -Wwrite-strings

Durak: main.cpp
	g++ ${CFLAGS} -o Durak main.cpp
clean:
	rm -f Durak
