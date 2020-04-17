// Gregory Giovannini
// Problem 2
// signalTree.c

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

char processNames[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
					     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
						 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


int main(int argc, char* argv[])
{
	// Error check on input, the length of the list.
    if (argc != 1)
    {
        printf("Invalid arguments: 0 expected, %d provided.", argc - 1);
        return -1;
    }

	size_t i;
	pid_t pid;
	for (i = 0; i < 26; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			// Error.
			printf("Error forking new process.\n");
			exit(-1);
		}
		else if (pid > 0)
		{
			// Parent.

		}
		else
		{
			// Child.

		}
	}

}
