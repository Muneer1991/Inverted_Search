SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c, %.o, $(SRC))

out.exe: $(OBJ)
	gcc -o $@ $(OBJ)

clean:
	rm *.o *.exe
