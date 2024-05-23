
make:
	gcc -Wall -o random random.c binarytree.c rbtree.c

clean:
	rm -rf random
