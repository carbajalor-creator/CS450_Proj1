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
	
	// just trying to detect 'ps'
	
	

        for (int i=0; i < num_words; i++) {
            printf("%s\n", line_words[i]);
        }


	printf("Index 0: %s\n", line_words[0]);

	pid_t x = fork();

	if (x < 0) {
	
	    printf("fork failed\n");
	    exit(1);
	} else if (x == 0) {
	  // printf("I'm a child process!\n");
	   execlp(line_words[0], line_words[0], line_words[1], line_words[2], NULL);
	   perror("didn't exec properly");
	} else {
	//	printf("I'm the parent process!\n");
		wait(NULL);
	
	}
    }	

    
    return 0;
}


