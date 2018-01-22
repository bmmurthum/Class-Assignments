# Process Management Concepts

This document is an exercise and review of the mechanisms used in UNIX/Linux systems for process creation, execution management, blocking and termination. In C, this will be an exercise of `fork()`, `exec()`, `wait()`, and `exit()` system calls.

The sample programs are directly sourced from an assignment by Prof. Hans Dulimarta.

## Contents

- Process Creation
- Process Suspension and Termination
- Process Execution
- Discussion of Exercise Assignment
- Source of Exercise Assignment

## Process Creation

**Sample Program #1:**

```C
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  puts("Before fork");
  fork();
  sleep(3);
  puts("After fork");
  return 0;
}
```

Running the previous program:

```
>> ./a.out
Before fork
After fork
After fork
```

**Why did this happen?**

Stepping through the program, we can see that `puts("Before fork")` will only be called once. Then, `fork()` births another process identical to this program with the program counter at the same location. Then each of these two processes, the parent and the child, independently run to their completition--both running their own `puts("After fork")`.

**Observing the process info:**

By running our program with `&` appended to the end, we can run our command in background mode. In our case, something like `./a.out&`. In the moment of the program stalling on the `sleep()` method, we can run the "ps" utility in verbose mode to see details of which processes are running and some related information to each process. We do with with the command `ps -v`.

The `ps -v` command returns details such as:
- Percentage of system memory being used. 
- RSS: "resident set size," the memory size of the process in 1024 byte units.
- STAT: the process state code. (S, sleeping; T, stopped; Z, defunct-zombie)
- PID: Process ID

The command `kill 1234` can then be used, for example, to stop a malfunctioned process that has the PID "1234".

**Sample Program #2:**

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int i, limit;

    if (argc < 2) {
	fputs("Usage: must supply a limit value\n", stderr);
	exit(1);
    }
    limit = atoi(argv[1]);

    fork();
    fork();
    printf("PID#: %d\n", getpid());
    for (i = 0; i < limit; i++)
	printf("%d\n", i);
    return 0;
}
```

**Program Output:**

```
>> a.out 3
PID#: 3713
0
1
2
PID#: 3715
0
1
2
PID#: 3714
0
1
2
PID#: 3716
0
1
2
```

**Description of Output:**

The previous program executes `fork()` twice, showing us an interesting output. A critical thing to observe here is the behavior of our OS's process scheduling. By running this, we can see that the OS gives each one of these child processes runtime one after another (noting that the PID may potentially not be in sequencial order). In a system with multiple cores, they may run concurrently, and without precise pattern of which to finish first.

**Illustration of the Processes:**

*Link an image here.*

## Process Suspension and Termination

Here we will look at the `wait()` system call and the `exit()` function as related to the parent-child relationship.

**Sample Program #3:**

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    // Use these variables
    pid_t pid, child;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork failure");
        exit(1);
    }
    else if (pid == 0) {
        printf("I am child PID %ld\n", (long) getpid());
        /* insert an appropriate form of the exit() function here */
    }
    else {
	child = wait(&status);
        printf("Child PID %ld terminated with return status %d\n", (long) child, WEXITSTATUS(status));
    }
    return 0;
}
```

**Program Output:**

```
>> a.out
```

In the previous program, we can see that the child will output to the terminal first. This is because the parent process is stuck on the `wait()` until the child finishes, then to run his `printf()`.

MORE HERE.

## Process Execution

The `exec()` family of system calls allow us to specify that a process, potentially a just-spawned-child, should be overlayed with a new executable. This process will then execute different code than its parent. There are several forms of `exec()` that exist. These allow for flexibilities of use of vectors, pointers, path variables, and environment variables.

The following program shows one form of the `exec()` call. It is used to execute any command (such as `ls` or `ps`) that the user submits.

```C
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fputs("Usage: must supply a command\n", stderr);
        exit(1);
    }

    puts("Before the exec");
    if (execvp(argv[1], &argv[1]) < 0) {
        perror("exec failed");
        exit(1);
    }
    puts("After the exec");

    return 0;
}
```

**Program Output:**

```
>> a.out date
Before the exec
Man Jan 22 18:40:28 EST 2018
```

In viewing the output of the code, as seen in the last snippet, we can see that the `puts("After the exec")` is never called. In the successful execution of `execvp()`, our code is thrown out and replaced entirely by the code of the new process, never calling another line of our code. In the case that the user inputs an executable that our system cannot find, the `execvp()` will return a "-1", in which case the `perror("exec failed")` and `exit(1)` will be called.

## Discussion of Exercise Assignment

The program is meant to emulate the processes of a typical shell. Our example, runs within the shell to display the concept.

**Program Requirements**

- Display a prompt to the user.
- Get and parse the user input.
- Spawn a child process to execute the command.
- Find and use the appropriate system call to collect resource usage statistics about each executed process.
- Continue accepting commands until user types `quit`.

[Link](https://google.com) to the source code.