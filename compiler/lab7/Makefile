SHELL = /bin/sh

labreport: labreport.c
	gcc -o $@ $<
labreport.c: labreport.l
	flex -o $@ $<
