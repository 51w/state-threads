
all:
	gcc -c ../sync.c ../stk.c ../sched.c ../key.c ../md_cygwin64.S -DCYGWIN64 -I.
	ar rcs libst.a *.o
	rm *.o