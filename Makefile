
all:
	gcc sync.c stk.c sched.c key.c demo.c md_cygwin64.S -o demo -DCYGWIN64 -DMD_HAVE_SELECT -I.