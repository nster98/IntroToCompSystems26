# Problem 3

## Question 1

What happens if root process A is terminated prematurely, by issuing `kill -KILL <PID>`?

When the user kills the root process, the program will still run until it comes back to process A, where it won't be able to continue. This is in the sense that A's child processes are independent, and will run normally until finished and exited gracefully. When they exit and come back to processs A, it can't continue to make process C, since it has been killed.

## Question 2



## Question 3

What is the maximum tree you can generate? Why?

The maximum tree the user can generate is set by the ulimit of the system. The ulimit can be found by the command `ulimit -u`, which will give the maximum amount of processes the user can create. On the DSV machines, the user can create 31830 processes before errors start occuring when making the next process. This limit is set by the system administrator, and if it were to be higher, the machine wouldn't be able to handle that many processes. Thus, the maximum tree the user can generate is a tree with 31830 processes.
