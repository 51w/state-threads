
all:
	gcc -c ../sync.c ../stk.c ../sched.c ../key.c ../md_cygwin64.S -I. -O2 
	ar rcs libst.lib *.o
	rm *.o