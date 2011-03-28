
build: clean
	gcc -o bin/build src/build.c
	gcc -o bin/prepare src/prepare.c
	chmod +x bin/*

clean:
	rm -fr data/prep.data
	rm -fr bin/*
