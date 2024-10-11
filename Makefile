#############################################################################################################
# gcc sync.c stk.c sched.c key.c demo.c asm/make_gas.S asm/jump_gas.S -o demo -DCMINGW64 -DMD_HAVE_SELECT -I.

all:
	gcc sync.c stk.c sched.c key.c demo.c asm/make_gas.S asm/jump_gas.S -o demo -I.
