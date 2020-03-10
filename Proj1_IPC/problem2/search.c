// Nathan Glikman
// Gregory Gionvaninni
// Problem 2
// search.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <sys/wait.h>
#include <sys/types.h>

int search(int* arr, int size, int factor, int key)
{
	int amount = size / factor;
	int status;
	int sectionOfChild[factor];
	pid_t pid[factor];
		
	// Create a number of forks equal to size
	for (int i = 0; i < size; i += amount)
	{
		//pid[i / amount] = fork();
		
	}
	
	return 0;	
}


int main(int argc, char* argv[])
{
	int const MAX_NUM = 40;
		
	int arr[MAX_NUM];

	FILE* file = fopen("arrayNums.txt", "r");

	for (int i = 0; i < MAX_NUM; i++)
	{
		if (fscanf(file, "%d", &arr[i]) != 1)
			break;
		printf("arr[%d] = %d\n", i, arr[i]);
	}	
}
