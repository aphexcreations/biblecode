
build: clean
	gcc -o bin/prepare src/prepare.c
	gcc -o bin/build -I ext/uthash/src/ src/build.c
	chmod +x bin/*

clean:
	rm -fr data/prep.data
	rm -fr bin/*
