demo-gtk2 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk+-2.0`

demo-gtk3 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk+-3.0`

demo-gtk4 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk4`

all:
	demo-gtk2 demo-gtk3 demo-gtk4
