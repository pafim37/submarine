APPNAME=a.exe
SRCS=main_menu.cpp

CC=x86_64-w64-mingw32-g++
CFLAGS=-o $(APPNAME) -Wall -O2
ALLEGRO=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`
.PHONY: all main

all: clear main open 

clear:
	clear
main:
	$(CC) $(CFLAGS) $(SRCS) $(ALLEGRO)

open:
	./a.exe

