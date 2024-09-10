#include <stdio.h>
//#include <iostream>
#include "public.h"
st_cond_t cond;

void* start1(void *arg) {
	for (int i = 0; i < 10; i++) {
        printf("AAA-->%d<<\n", i);
        st_sleep(1);
		st_thread_yield();
    }
	return NULL;
}
void* start2(void *arg) {
	for (int i = 0; i < 10; i++) {
        printf("BBB-->%d<<\n", i);
        //st_sleep(1);
		st_thread_yield();
    }
	return NULL;
}

extern st_utime_t st_utime(void);

void* start3(void *arg) {
	for (int i = 0; i < 10; i++) {
		//st_utime_t now = st_utime();
        //printf("AAA-->%d=======\n", i);
        
		st_usleep(1);
		st_cond_broadcast(cond);
    }return NULL;
}
void* start4(void *arg) {
	for (int i = 0; i < 100; i++) {
		st_utime_t now = st_utime();
        printf("BBB-->%d=======\n", i);
		//st_cond_wait(cond);
		st_cond_timedwait(cond, 100*1000000);
    }return NULL;
}

void* start5(void *arg) {
	st_netfd_t server = st_netfd_open_tcp("192.168.0.2", 8000);
	st_listen(server, ST_UTIME_NO_TIMEOUT);
	while(1){
		st_sleep(10);
		printf("=======srs_accept\n");
	}
}

int main(int argc, char** argv)
{
	printf("=======00\n");
	//std::cout << "aaaaaaa";

    st_init();
	
	cond = st_cond_new();

	st_thread_create(start1, NULL, 0, 0);
	st_thread_create(start2, NULL, 0, 0);
	st_thread_create(start5, NULL, 0, 0);
	printf("=======11\n");
	
	
	while(1){
		st_sleep(3600);
		//printf("=======zz\n");
	}
	st_thread_exit(NULL);
	printf("=======\n");
    return 0;
}

