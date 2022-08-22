ssdsim: main.c ssd.c list.c keyval.c
	gcc -o ssdsim main.c ssd.c list.c keyval.c -I.
	mkdir -p files
