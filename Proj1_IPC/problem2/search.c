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

int* search(int* arr, int size, int factor, int key, int foundIndex[])
{	
	int amount = size / factor;
	int status;
	int sectionOfChild[factor];
	pid_t pid[factor];

	unsigned char exit_code;

	int foundIndexI = 0;
		
	int num;
	// Create a number of forks equal to size
	for (int i = 0; i < size; i += amount)
	{
		pid[i / amount] = fork();
		num = i;

		if (pid[num / amount] < 0) // Error
		{
			fprintf(stderr, "Failed to fork\n");
			exit(-1);
		}

		if (pid[num / amount] == 0) // Child
		{
			printf("I am process %d, my parent is %d\n", getpid(), getppid());
			
			int foundFlag = 0;

			int end = (num + amount < size) ? num + amount : size;

			for (int j = num; j < end; j++)
			{
				if (arr[j] == key)
				{
					foundFlag = 1;
					//foundIndex[foundIndexI++] = j;
					exit(j % amount);
				}
			}
			if (foundFlag == 0)
			{
				exit(-1);
			}
		}
		else // Parent
		{
			
		}
	}

	int k;
	for (k = 0; k < amount; k++)
	{
		waitpid(pid[k], &status, 0);
		sectionOfChild[k] = k * amount;

		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);

			if (exit_code != 255)
			{
				break;
			}
		}
	}

	if (exit_code < 255)
	{
		printf("I am process %d and I found the key at %d\n", pid[k], exit_code + sectionOfChild[k]);	
	}	

	return foundIndex;
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
		//printf("arr[%d] = %d\n", i, arr[i]);
	}

	// Set the keys at each point in the array
	int key = -50;
	arr[MAX_NUM / 4] = key;
	arr[MAX_NUM / 2] = key;
	arr[(3 * MAX_NUM) / 4] = key; 

	int factor = 4; // Amount of processes to make
	
	int ulimit = 31830; // ulimit set by DSV 

	if (factor > ulimit)
	{
		printf("Went over ulimit, stopping program...\n");
		return 0;
	}	
	
	int* foundIndex = (int*) malloc(sizeof(int) * 3);

	foundIndex = search(arr, MAX_NUM, factor, key, foundIndex);

	for (int i = 0; i < 3; i++)
	{
		printf("Key found at index: %d\n", foundIndex[i]); // DOESNT WORK
	}

	// THOUGHTS
	//
	// There needs to be something like an array for the process to put its found index for the key into
	// They should also have a maximum that is sent to each process whenever one of them finds something larger
}
