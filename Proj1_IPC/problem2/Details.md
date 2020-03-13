# Problem 2
The goal of this problem is to explore the effect of various process structures on a practical application - the searching of a list for 3 given indices, as well as determining the maximum element in the list.

In these problems, we assume that each process will search a sub-list consisting of at most 250 elements, except in the variation, in which we increase that number to 1000 per process.

## Question 1
In this part, a single process is used to sequentially search the list for the 3 indices and the max. However, the process may not terminate as soon as the three elements are found; it must run until the end of the list, in order to determine with certainty the value of the maximum element in the list.

Based on the results in timeResults.txt, this method seems to be the fastest compared to the later variations. The reason for this is likely due to the massive overhead involved in forking new processes, which this part does not involve.

## Question 2
In this part, a chain of processes is used to search the list for the 3 indices and the max. Because we are limited to only spawning a single process at a time, the structure of the process "tree" looks more like a linked list of processes. 

Based on the results in timeResults.txt, this method seems to be the slowest compared to the later variations. The reason is simple: we are creating a massive chain of processes, each dependent on one another, and even though each is searching concurrently, the creation of a new process must wait for the previous process in the chain to finish being created. Thus, the large overhead that comes with forking is extremely detrimental to the runtime of this algorithm.

Additionally, the 

## Question 3
In this part, 

## Variation on the Question