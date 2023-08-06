###
### All target. Maybe at some point we will have some deps too
###

all: demo-gtk2 demo-gtk3 demo-gtk4 builder-gtk2 builder-gtk3 builder-gtk4

###
### Basic GTK Demos
###

demo-gtk2 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk+-2.0`

demo-gtk3 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk+-3.0`

demo-gtk4 :
	gcc -o $@ main.c `pkg-config --libs --cflags gtk4`

###
### GTK Builder Demos for each version of the library
### (disabled for now)

#builder-gtk2 :
#	gcc -o $@ $@.c `pkg-config --libs --cflags gtk+-2.0`

#builder-gtk3 :
#	gcc -o $@ $@.c `pkg-config --libs --cflags gtk+-3.0`

#builder-gtk4 :
#	gcc -o $@ $@.c `pkg-config --libs --cflags gtk4`

###
### Generic Builder for all GTK Versions
###

builder-gtk2 :
	gcc -o $@ builder-gtk-all.c `pkg-config --libs --cflags gtk+-2.0`

builder-gtk3 :
	gcc -o $@ builder-gtk-all.c `pkg-config --libs --cflags gtk+-3.0`

builder-gtk4 :
	gcc -o $@ builder-gtk-all.c `pkg-config --libs --cflags gtk4`

###
### Clean target, other useful targets
###

clean:
	rm -f demo-gtk2 demo-gtk3 demo-gtk4 builder-gtk2 builder-gtk3 builder-gtk4

