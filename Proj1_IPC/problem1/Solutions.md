# 332:579 Computer System Project 1



## Problem1



### Part1: 

command: `$gcc –Wall –o myfunc.c myfunc.c`

`gcc` is the compiler for c programming language, it has many flags. Flag `-Wall` will show all the warnings during the file compiling. For the flag of `-o`, it will compile the second argument (a c file) after `-o` into an executable file named same as the first argument after `-o`. So this command will compile c file `myfunc.c` into executable file `myfunc.c`. Then `myfunc.c` will be overwritten with the compilation of this command, which would cause the data loss.