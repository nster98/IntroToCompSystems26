// Gregory Giovannini
// Problem 1 Question 1
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
#include <string.h>
#include <pthread.h>

int search(int *arr, int size, int xThreads, int key, int *foundIndexes);
void *atomicSearch(void *threadArgs);

#define KEY -50

typedef struct {
	int foundMax;
	int foundCount;
	int *foundIndexes;
} ThreadOutputs;

typedef struct {
	ThreadOutputs *threadOutputs;
	int *arr;
	int size;
	int startIndex;
	int stopIndex;
	int key;
} ThreadInputs;


int search(int *arr, int size, int xThreads, int key, int *foundIndexes)
{


	return 1;
}


void* atomicSearch(void *threadArgs)
{
	// Unpack the parameters.
	ThreadInputs *threadInputs = (ThreadInputs *) threadArgs;
	ThreadOutputs *threadOutputs = threadInputs -> threadOutputs;
	int* arr = threadInputs -> arr;
	int size = threadInputs -> size;
	int startIndex = threadInputs -> startIndex;
	int stopIndex = threadInputs -> stopIndex;
	int key = threadInputs -> key;

	// Initialize the search.
	int foundCount = 0;
	int max = arr[startIndex];
	size_t i;

	for (i = startIndex; i < size && i < stopIndex; i++)
	{
		// Max check.
		if (arr[i] > max)
		{
			max = arr[i];
		}
		// Key check.
		if (arr[i] == key)
		{
			threadOutputs -> foundIndexes[foundCount++] = i;
			threadOutputs -> foundCount = foundCount;
			printf("I am pthread %d and I found the key at %zu\n", (int) pthread_self(), i);
		}
	}

	// Save the maximum.
	threadOutputs -> foundMax = max;

	return threadOutputs;
}


int main(int argc, char* argv[])
{
	// Error check on input, the length of the list.
    if (argc != 3)
    {
        printf("Invalid arguments: 2 expected, %d provided. \nRequires two integers: the length of the list to search, and the number of threads that can be created.\n", argc - 1);
        return -1;
    }
    int listSize = atoi(argv[1]);
	int xThreads = atoi(argv[2]);

	// Check to make sure the number of threads requested is not too high.
	// TODO

	int arr[listSize];

	// Read in the input list from the file.
	FILE* file = fopen("arrayNums.txt", "r");
	int i;
	for (i = 0; i < listSize; i++)
	{
		if (fscanf(file, "%d", &arr[i]) != 1)
			break;
	}

	// Set the keys at each point in the array.
	int key = KEY;
	arr[listSize / 4] = key;
	arr[listSize / 2] = key;
	arr[(3 * listSize) / 4] = key;


	// Start timing here.
	struct timeval start, end, diff;
    gettimeofday(&start, NULL);

	int* foundIndexes = (int*) malloc(sizeof(int) * 3);
	search(arr, listSize, xThreads, key, foundIndexes);

	for (i = 0; i < 3; i++)
	{
		printf("Key found at index: %d\n", foundIndexes[i]);
	}

	// Stop timing here.
	gettimeofday(&end, NULL);
    timersub(&end,   &start, &diff);

	printf("Search took %'8.3f ms.\n", diff.tv_sec*1000.0 + diff.tv_usec/1000.0);
}
