/*******************************************************************************

CIS 452 Lab Programming Assignment. This program emulates a simple shell. It
displays an understanding of process management in a UNIX system.

The program does several things.
- Initially prompts the user
- Gets and parses the user's input
- Spawns a child process to execute the command
- Prints resource usage statistics about each executed process
- Quits upon user entry "quit" 

 @author   - Joseph Cutino, Brendon Murthum
 @version  - Winter 2018 

*******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TEXT_BUFFER 255
#define DEBUGGING 0	

int main(int argc, char* argv[]) {	

	/** Keeps the program running. */
	int monitor = 1;
	/** User's originally typed input. */
	char text[TEXT_BUFFER];
	/** An individual string parsed from original text. Helper variable. */
	char *token;
	/** User's typed in commands. Parsed from original input. */
	char *cmd[10];
	/** For iteration. */
	int i = 0;
	/** Process addresses. For managing children. */
	pid_t pid, wpid;

    /** Display a prompt to the user. */
	printf("Simple Shell:\n");
	
	// Runs until user quits the program.
	while (monitor) {
		i = 0;
		printf(">> ");
		
		// Read line into character array.
		if (fgets(text, TEXT_BUFFER, stdin) != NULL) {
			// Remove newline character if present.
			if (text[strlen(text)-1] == '\n'){
				text[strlen(text)-1] = '\0';
			}
			
			// Validates the input to have more than spaces alone. 
			int j;
			bool check = false;
			for (j = 0; j < (int)strlen(text); j++) {
			    if (text[j] != ' ') {
			        check = true;
			        break;
			    }
			}
			if (check == false) {
			    printf("Must enter valid input...\n\n");
			    continue;
			}
			
			// Tokenize the input.
			token = strtok(text, " ");
			while(token != NULL){
				cmd[i] = token;
				if(DEBUGGING){
					printf("%s\n",token);
				}
				i++;
				token = strtok(NULL, " ");
			}
			
			// Argument list must terminated by NULL.
			cmd[i] = NULL; 
			
			// Stops the program upon user entry "quit".
			if (strcmp(cmd[0],"quit") == 0) {
				monitor = 0;
				printf("Thank you for using this primitive shell.\n");
			} else {
			
				// Create child process to run command. 
				pid = fork();
				if (pid == 0){
				
					// Child
					if (execvp(cmd[0],cmd) < 0) {
						perror("exec failed");
						exit(7);
					}
					
				} else {
					int status;
					wpid = wait(&status);
					
					// Print usage stats.
					struct rusage usage;
					struct timeval time;
					int rtnstat;
					rtnstat = getrusage(RUSAGE_CHILDREN, &usage);
					time = usage.ru_utime;
					long switches = usage.ru_nivcsw;
					
					/* 
					 Print user CPU time used and number of involuntary 
					 context switches for each child process. 
					*/
					printf("\nCPU TIME USED: %ld.%lds\n", 
					        time.tv_sec,time.tv_usec);
					printf("Involuntary Context Switches: %ld\n\n", switches);
				}
			}	
		}	
	}
	
	return 0;
}	


