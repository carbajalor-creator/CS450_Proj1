#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "constants.h"
#include "parsetools.h"



void simplecommands(char *arr[]) {
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		printf("failed fork\n");
		exit(1);

	} else if (pid == 0) { //child process
		execvp(arr[0], arr);
		perror("if you see this..something has gone wrong.\n");
		
	} else { wait(NULL); } // parent process waits and reaps child

}



int main() {

    // Buffer for reading one line of input
    char line[MAX_LINE_CHARS];
    // holds separated words based on whitespace
    char* line_words[MAX_LINE_WORDS + 1];
    // True when stdin is connected to a terminal
    int interactive = isatty(STDIN_FILENO);

    // Loop until user hits Ctrl-D (end of input)
    // or some other input error occurs
    while (1) {
        if (interactive) {
            printf("lobo> ");
            fflush(stdout);
        }
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }

        int num_words = split_cmd_line(line, line_words);
	// passing line_words into simplecommands(arr);
	// Will need a way to distinguish between simple commands 
	// and those with pipes.
	simplecommands(line_words);	
	
	
	
    }
    return 0;
}


