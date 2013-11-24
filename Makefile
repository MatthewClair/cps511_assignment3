CC = g++
OBJ = build/main.o build/global.o build/Vector3D.o
BIN = main
FLAGS = -lGL -lGLU -lglut -Wall -Werror -std=c++11 -Wdouble-promotion

$(BIN): $(OBJ) Makefile
	$(CC) $(FLAGS) -o $(BIN) $(OBJ)

build/global.o: global.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/main.o: main.cpp modules/Vector3D/Vector3D.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Vector3D.o: modules/Vector3D/Vector3D.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@echo cleaning
	@rm -f $(BIN) $(OBJ)
