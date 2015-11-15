project :
	gcc te.c -ansi -o project `pkg-config --cflags --libs gtk+-2.0`
	
