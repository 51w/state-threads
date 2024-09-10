#include <stdio.h>
#include <public.h>
st_cond_t cond;

void* start1(void *arg) {
	for (int i = 0; i < 10; i++) {
        fprintf(stderr, "AAA-->%d<<\n", i);
        //st_sleep(1);
		st_thread_yield();
    }
	return NULL;
}
void* start2(void *arg) {
	for (int i = 0; i < 10; i++) {
        fprintf(stderr, "BBB-->%d<<\n", i);
        //st_sleep(1);
		st_thread_yield();
    }
	return NULL;
}

void* start3(void *arg) {
	for (int i = 0; i < 10; i++) {
        fprintf(stderr, "AAA-->%d=======\n", i);
        
		st_sleep(1);
		st_cond_broadcast(cond);
    }return NULL;
}
void* start4(void *arg) {
	for (int i = 0; i < 10; i++) {
        fprintf(stderr, "BBB-->%d=======\n", i);
		st_cond_wait(cond);
    }return NULL;
}

int main(int argc, char** argv)
{
	printf("=======00\n");

    st_init();
	
	cond = st_cond_new();

	st_thread_create(start1, NULL, 0, 0);
	st_thread_create(start2, NULL, 0, 0);
	fprintf(stderr, "=======11\n");

	st_thread_create(start3, NULL, 0, 0);
	st_thread_create(start4, NULL, 0, 0);
	fprintf(stderr, "=======11\n");

	st_thread_exit(NULL);
	fprintf(stderr, "=======\n");
    return 0;
}

