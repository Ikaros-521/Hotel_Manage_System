CC=g++
LIB=-lm
OBJ=class.o tools.o main.o
BIN=hotel
FLAG=-Wall

all:$(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BIN)
%.o:%.cpp
	$(CC) $(FLAG) $(INC) -c $< -o $@

clean:
	rm $(OBJ) $(BIN)

