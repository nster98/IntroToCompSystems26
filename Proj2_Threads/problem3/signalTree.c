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
#include <signal.h>

char processNames[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
					     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
						 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

size_t processNum = -1;  // Initial process is -1; root process will be 0, child will be 1, and so on.
pid_t processList[26];

void continueHandler(int signum)
{
	printf("Process %c received SIGCONT.\n", processNames[processNum]);
}

void explain_wait_status(pid_t pid, int status)
{
	if (WIFEXITED(status))
	{
		fprintf(stderr, "Child with PID = %ld terminated normally, exit status = %d.\n",
			(long) pid, WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		fprintf(stderr, "Child with PID = %ld was terminated by a signal, signo = %d.\n",
			(long) pid, WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
	{
		fprintf(stderr, "Child with PID = %ld has been stopped by a signal, signo = %d.\n",
			(long) pid, WSTOPSIG(status));
	}
	else
	{
		fprintf(stderr, "%s: Internal error: Unhandled case, PID = %ld, status = %d.\n",
			__func__, (long) pid, WEXITSTATUS(status));
		exit(1);
	}
	fflush(stderr);
}

int main(int argc, char* argv[])
{
	// Error check on input, the length of the list.
    if (argc != 1)
    {
        printf("Invalid arguments: 0 expected, %d provided.", argc - 1);
        return -1;
    }

	signal(SIGCONT, continueHandler);
	size_t i;
	pid_t pid;
	int status;

	int fd[2];
	if (pipe(fd) == -1)
	{
		printf("Error: could not create pipe.\n");
		exit(-1);
	}

	// Create the root process.
	pid = fork();
	if (pid < 0)
	{
		// Error.
		printf("Error forking new process.\n");
		exit(-1);
	}
	else if (pid > 0)
	{
		// Parent - this process is the INITIALIZER.
		processNum = -1;
	}
	else
	{
		// Child - this process is the ROOT.
		processNum = 0;
		processList[0] = getpid();
		write(fd[1], &(processList[0]), sizeof(pid_t));

		// Let the root create its chain.
		pid = fork();
		if (pid < 0)
		{
			// Error.
			printf("Error forking new process.\n");
			exit(-1);
		}
		for (i = 1; i < 26; i++)
		{
			if (pid > 0)
			{
				// Parent.

				// Wait for children.
				pid = wait(&status);
				explain_wait_status(pid, status);

				if (WIFSTOPPED(status))
				{
					// Suspend.
					printf("Suspending process %d.\n", getpid());
					raise(SIGTSTP);

					// When resuming, send SIGCONT to child.
					printf("Resuming process %d.\n", pid);
					kill(pid, SIGCONT);
				}
				else
				{
					// Something went wrong.
					printf("Error...\n");
				}
			}
			else
			{
				// Child.
				processNum = i;
				processList[i] = getpid();
				write(fd[1], &(processList[i]), sizeof(pid_t));
				
				pid = fork();
				if (pid < 0)
				{
					// Error.
					printf("Error forking new process.\n");
					exit(-1);
				}
			}
		}
	}
	
	if (processNum == -1)
	{
		// Initializer.

		// Display the process tree.
		for (i = 0; i < 26; i++)
		{
			read(fd[0], (processList + i), sizeof(pid_t));
			if (i == 25)
			{
				printf("%c\n", processNames[i]);
			}
			else
			{
				printf("(%c) -> \n", processNames[i]);
			}
		}

		// Wait 5 seconds.
		sleep(5);

		// Send SIGCONT to root.
		printf("Resuming process %d.\n", processList[0]);
		kill(processList[0], SIGCONT);
		
		printf("All processes terminated.\n");
	}
	else if (processNum == 26)
	{
		// Last child process.

		// Suspend.
		raise(SIGTSTP);

		printf("Process %c terminating.\n", processNames[processNum]);
	}
	else
	{
		// Simply terminate.
		printf("Process %c terminating.\n", processNames[processNum]);
	}
	
	return 0;
}
