
CUR_DEF = -DCYGWIN64 -DMD_HAVE_SELECT 
CUR_INC = -I. -I./libuv/include 
CUR_LIB = -L./libuv/lib -luv -lpsapi -luser32 -ladvapi32 -liphlpapi -luserenv -lws2_32 -ldbghelp -lole32 -lshell32

all:
	gcc sync.c stk.c sched.c key.c demo.c md_cygwin64.S -o demo $(CUR_DEF) $(CUR_INC) $(CUR_LIB)