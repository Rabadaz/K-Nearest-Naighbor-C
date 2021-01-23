build: src/main.c
	gcc -o knn -Wincompatible-pointer-types src/main.c
run: build
	./knn

clean: src/main.c
	rm -f ./knn
	rm -Rf ./src/main.dSYM
	rm -f ./src/main
