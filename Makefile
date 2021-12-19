Projeto = MatMulti

C_SOURCE = $(wildcard ./src/*.c)
H_SOURCE = $(wildcard ./src/*.h)

OBJ = $(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

CC = gcc

CC_FLAGS=-c	\
		 -W	\
		 -Wall	\
		 -std=c99	\
		 -lpthread	\
		 -pedantic


all: objFolder $(Projeto)

$(Projeto):	$(OBJ)
	@ echo 'Compilando binários do projeto: $@'
	$(CC) $^ -o $@ -lpthread
	@ echo 'Compilação finalizada do projeto: $@'

./objects/%.o: ./src/%.c ./src/%.h
	@ echo 'Compilando o arquivo $<'
	$(CC) $< $(CC_FLAGS) -o $@

./objects/main.o: ./src/main.c $(H_SOURCE)
	@ echo 'Compilando o arquivo $<'
	$(CC) $< $(CC_FLAGS) -o $@


objFolder:
	@ mkdir -p objects
	@ mkdir -p Resultados

clean:
	@ rm -rf ./objects/*.o $(Projeto) Pth_Registro_Mat.txt *~
	@ rm -rf ./Resultados/*.txt
	@ rmdir Resultados
	@ rmdir objects

.PHONY: all clean