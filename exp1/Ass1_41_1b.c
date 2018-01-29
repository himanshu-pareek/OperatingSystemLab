/*
	OPERATING SYSTEM LABORATORY
	ASSIGNMENT # 01 (B)
	GROUP	   # 41
	DHIRAJ KUMAR TANDI (15CS30013)
	HIMANSHU PAREEK (15CS30016)
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_WORDS 	10
#define MAX_LEN		100

int max (int a, int b) {
	return (a > b) ? a : b;
}

void runExeclp (char* s) {
	execlp("sh", "sh","-c",s, NULL);
}

int main (void) {
	pid_t child;
	int   cstatus;	/* Exit status of child. */
	pid_t c;		/* Pid of child to be returned by wait. */
	
	char s[MAX_LEN];
	printf ("------------------ New Shell for executing commands-------------------\n---------- (type \"quit\" (without quotes) and press ENTER to exit------\n\n");
	printf ("$ :");
	scanf ("%[^\n]", s);
	
	while (strcmp (s, "quit")) {
		
		if ((child = fork ()) == 0) {
			/* Child process. To begin with, it prints its pid. */
			// printf ("Child: PID of child = %ld\n", (long) getpid ());
	
			// char s[MAX_LEN];
			// scanf ("%[^\n]", s);
			runExeclp (s);
	
			/* If the child process reaches this point, then */
			/* execlp must have failed.						 */
			fprintf (stderr, "Child process could not do execlp.\n");
			exit (1);
		} else {
			/* Parent process. */
			if (child == (pid_t)(-1)) {
				// Fork failed
				fprintf (stderr, "Fork failed.\n");
				exit (1);
			} else {
				c = wait (&cstatus); // Wait for child to complete.
				// printf ("Parent : Child %ld exited with status = %d\n", (long) c, cstatus);
				getchar ();
				printf ("$ :");
				scanf ("%[^\n]", s);
			}
		}
	}
	
	return 0;
} /* End of main. */


