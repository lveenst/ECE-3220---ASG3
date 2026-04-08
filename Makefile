# makefile for asg3

comp = gcc
comp_flags = -Wall

Raid5 : Raid5.c
	$(comp) $(comp_flags) Raid5.c -o Raid5 $(comp_libs)

clean :
	rm -f Raid5 core