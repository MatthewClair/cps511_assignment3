CC = g++
OBJ = build/main.o build/global.o build/Vector3D.o build/DrawableEntity.o \
	  build/Player.o build/Light.o build/Enemy.o build/Projectile.o \
	  build/Colour.o build/Quad.o build/World.o build/Ship.o
BIN = main
FLAGS = -lGL -lGLU -lglut -Wall -Werror -std=c++11 -Wdouble-promotion -I./

$(BIN): $(OBJ) Makefile
	$(CC) $(FLAGS) -o $(BIN) $(OBJ)

build/global.o: global.cpp global.h modules/Player/Player.h \
	modules/World/World.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/main.o: main.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/DrawableEntity.o: modules/DrawableEntity/DrawableEntity.cpp \
	modules/DrawableEntity/DrawableEntity.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Ship.o: modules/Ship/Ship.cpp modules/Ship/Ship.h \
	modules/DrawableEntity/DrawableEntity.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Player.o: modules/Player/Player.cpp modules/Player/Player.h \
	modules/Ship/Ship.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Enemy.o: modules/Enemy/Enemy.cpp modules/Enemy/Enemy.cpp \
	modules/Ship/Ship.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Vector3D.o: modules/Vector3D/Vector3D.cpp Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Light.o: modules/Light/Light.cpp modules/Light/Light.h \
	modules/DrawableEntity/DrawableEntity.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Projectile.o: modules/Projectile/Projectile.cpp \
	modules/Projectile/Projectile.h modules/DrawableEntity/DrawableEntity.h \
	Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Colour.o: modules/Colour/Colour.cpp modules/Colour/Colour.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/Quad.o: modules/Quad/Quad.cpp modules/Quad/Quad.h \
	modules/Vector3D/Vector3D.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

build/World.o: modules/World/World.cpp modules/World/World.h Makefile
	$(CC) $(FLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@echo cleaning
	@rm -f $(BIN) $(OBJ)

# vim: noet ts=4 sw=4
