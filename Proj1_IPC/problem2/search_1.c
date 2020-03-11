// Nathan Glikman
// Gregory Giovannini
// Problem 2 Question 1
// search_1.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

int* search(int* arr, int size, int factor, int key, int foundIndex[]);


#define KEY -50

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
	// Error check on input, the length of the list.
    if (argc != 2)
    {
        printf("Invalid arguments: 1 expected, %d provided. \nRequires a single number, the length of the number list to search.\n", argc - 1);
        return -1;
    }
    int LIST_SIZE = atoi(argv[1]);

	int arr[LIST_SIZE];

	FILE* file = fopen("arrayNums.txt", "r");

	int i;
	for (i = 0; i < LIST_SIZE; i++)
	{
		if (fscanf(file, "%d", &arr[i]) != 1)
			break;
	}

	// Set the keys at each point in the array
	int key = -50;
	arr[LIST_SIZE / 4] = key;
	arr[LIST_SIZE / 2] = key;
	arr[(3 * LIST_SIZE) / 4] = key;

	int factor = 4; // Amount of processes to make
	int ulimit = 31830; // ulimit set by DSV 

	if (factor > ulimit)
	{
		printf("Went over ulimit, stopping program...\n");
		return -1;
	}


	// Start timing here.
	struct timeval start, end, diff;
    gettimeofday(&start, NULL);

	int* foundIndex = (int*) malloc(sizeof(int) * 3);
	foundIndex = search(arr, LIST_SIZE, factor, key, foundIndex);

	for (i = 0; i < 3; i++)
	{
		printf("Key found at index: %d\n", foundIndex[i]); // DOESNT WORK
	}

	// Stop timing here.
	gettimeofday(&end, NULL);
    timersub(&end,   &start, &diff);

	printf("Search took %'8.3f ms.\n", diff.tv_sec*1000.0 + diff.tv_usec/1000.0);

	// THOUGHTS
	//
	// There needs to be something like an array for the process to put its found index for the key into
	// They should also have a maximum that is sent to each process whenever one of them finds something larger
}
