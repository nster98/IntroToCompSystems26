// Problem 4

#define _POSIX_SOURCE
#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <float.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

// Mask 1 handles SIGINT
// Block SIGSTOP and SIGILL
void mask_sig1(void)
{
	sigset_t mask1;
	sigemptyset(&mask1);

	sigaddset(&mask1, SIGSTOP);
	sigaddset(&mask1, SIGILL);

	pthread_sigmask(SIG_BLOCK, &mask1, NULL);
}

// Mask 2 handles SIGSTOP
// Block SIGINT and SIGILL
void mask_sig2(void)
{
	sigset_t mask2;
	sigemptyset(&mask2);

	sigaddset(&mask2, SIGINT);
	sigaddset(&mask2, SIGILL);

	pthread_sigmask(SIG_BLOCK, &mask2, NULL);
}

// Mask 3 handles SIGILL
// Block SIGINT and SIGSTOP
void mask_sig3(void)
{
	sigset_t mask3;
	sigemptyset(&mask3);

	sigaddset(&mask3, SIGINT);
	sigaddset(&mask3, SIGSTOP);

	pthread_sigmask(SIG_BLOCK, &mask3, NULL);
}

// Thread 1 will handle SIGINT
void *thread1(void* arg)
{
	mask_sig1();
	printf("Thread1\n");
}

// Thread 2 will handle SIGSTOP
void *thread2(void* arg)
{
	mask_sig2();
	printf("Thread2\n");
}

// Thread 3 will handle SIGILL
void *thread3(void* arg)
{
	mask_sig3();
	printf("Thread3\n");
}

void setup_sig_handler(void)
{
	//struct sigaction action;
}

int main(int argc, char* argv[])
{
	pthread_t tid[3];

	for (int i = 0; i < 3; i++)	
	{
		if (i == 0) pthread_create(&tid[i], NULL, thread1, (void *)&tid);
		if (i == 1) pthread_create(&tid[i], NULL, thread2, (void *)&tid);
		if (i == 2) pthread_create(&tid[i], NULL, thread3, (void *)&tid);
	}

	for (int i = 0; i < 3; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_exit(NULL);

	return 0;


}
