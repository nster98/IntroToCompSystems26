#Question 1

*Signal does not re-install itself*

When sending signals from the command line to the process, only SIGINT will be handled correctly. With the code written, the thread that isn't blocking SIGINT, which is Thread 1, will print out
"Recieved SIGINT". However, due to how signal handlers work, there is no way to pass the thread id to the handler, but we know based on analysis of the code that only Thread 1 is handling it.
By sending SIGILL or SIGSTOP however, the whole point of those two signals is to stop or kill the process. Since we are working with threads, there is only one process, which is main, and so main is
terminated, along with all threads. There is no way for the threads to handle SIGILL or SIGSTOP, since at least one thread is responsible for handling it. We can't block it, so nothing is printed
from the handler. This is all when sending the signal once. When sending the signal SIGINT again, the signal is not being re-installed. Thus, it will not print out "Recieved SIGINT".

*Signal does re-install itself*

The only difference when re-installing the signal is that the process will continue printing out "Recieved SIGINT" when that signal is sent.


#Question 2
