build: 
	gcc ./child.c -o ./child
	gcc ./parent.c -o ./parent

run: build
	./parent test.txt

clean:
	rm -f *.out

all: build
