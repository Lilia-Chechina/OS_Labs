build: 
	gcc ./child.c -o ./child
	gcc ./parent.c -o ./parent

run: build
	./parent file.txt

clean:
	rm -f *.out

all: run
