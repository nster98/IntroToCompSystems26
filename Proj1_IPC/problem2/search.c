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

	unsigned char exit_code;
		
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

			int foundFlag = 0;

			int end = (num + amount < size) ? num + amount : size;

			for (int j = num; j < end; j++)
			{
				if (arr[j] == key)
				{
					foundFlag = 1;
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

	for (int k = 0; k < amount; k++)
	{
		waitpid(pid[k], &status, 0);
		sectionOfChild[k] = k * amount;

		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
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
		//printf("arr[%d] = %d\n", i, arr[i]);
	}

	// Set the keys at each point in the array
	arr[MAX_NUM / 4] = -50;
	arr[MAX_NUM / 2] = -50;
	arr[(3 * MAX_NUM) / 4] = -50; 

	// THOUGHTS
	//
	// There needs to be something like an array for the process to put its found index for the key into
	// They should also have a maximum that is sent to each process whenever one of them finds something larger
}
