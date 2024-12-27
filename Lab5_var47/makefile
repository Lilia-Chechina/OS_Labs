SRC = main.cpp tree.cpp
OBJ = $(SRC:.cpp=.o)
SRC2 = client.cpp
OBJ2 = $(SRC2:.cpp=.o)
INCLUDE_DIR = /opt/homebrew/include
LIB_DIR = /opt/homebrew/lib

all: main client

main: $(OBJ)
	g++ -std=c++11 -o main $(OBJ) -L$(LIB_DIR) -lzmq

client: $(OBJ2)
	g++ -std=c++11 -o client $(OBJ2) -L$(LIB_DIR) -lzmq

.cpp.o:
	g++ -std=c++11 -I$(INCLUDE_DIR) -c $< -o $@

client.o: tree.h
main.o: tree.h
tree.o: tree.h

clean:
	rm -f main client $(OBJ) $(OBJ2)
# g++ -std=c++11 -I/opt/homebrew/include -L/opt/homebrew/lib -lzmq main.cpp tree.cpp -o main