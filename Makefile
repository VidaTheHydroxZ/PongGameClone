# Include paths
INC=-I./inc -I./vendor/SDL2/include

# Library paths 
LIB_PATH=-L./vendor/SDL2/lib/x64

# Libraries to link against
LIBS=-lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer

# DLL Path
DLL_PATH=./vendor/SDL2/lib/x64/SDL*.dll

build:
	gcc -Wall -std=c23 ${INC} ${LIB_PATH} ./src/*.c ${LIBS} -o game
	cp ${DLL_PATH} .

run:
	./game

clean:
	rm -f game.exe SDL2.dll SDL2_ttf.dll SDL2_mixer.dll