/*
	OPERATING SYSTEM LABORATORY
	ASSIGNMENT # 01 (A)
	GROUP	   # 41
	DHIRAJ KUMAR TANDI (15CS30013)
	HIMANSHU PAREEK (15CS30016)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define TOTAL_INTS 100
#define BUF_SIZE 10
#define MAX_NUM INT_MAX

void merge (int* a, int l, int m, int r) {
	int nl = m - l + 1;
	int nr = r - m;
	int i, j, k;
	int al[nl], ar[nr];
	for (i = 0; i < nl; i++) {
		al[i] = a[l + i];
	}
	for (j = 0; j < nr; j++) {
		ar[j] = a[j + m + 1];
	}
	i = j = 0;
	k = l;
	while (i < nl && j < nr) {
		if (al[i] > ar[j]) {
			a[k] = ar[j];
			j++;
		} else {
			a[k] = al[i];
			i++;
		}
		k++;
	}
	while (j < nr) {
		a[k++] = ar[j++];
	}
	while (i < nl) {
		a[k++] = al[i++];
	}
}

void mergeSort (int* a, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort (a, l, m);
		mergeSort (a, m + 1, r);
		merge (a, l, m, r);
	}
}

int* merge2 (int* a1, int* a2, int* a3, int n1, int n2, int n3) {
	int* a = (int *) malloc ((n1 + n2 + n3) * sizeof (int ));
	int i, j, k, m;
	i = j = k = m = 0;
	while (i < n1 && j < n2 && k < n3) {
		if (a1[i] <= a2[j] && a1[i] <= a3[k]) {
			a[m] = a1[i++];
		} else if (a2[j] <= a1[i] && a2[j] <= a3[k]) {
			a[m] = a2[j++];
		} else {
			a[m] = a3[k++];
		}
		m++;
	}
	while (i < n1 && j < n2) {
		if (a1[i] > a2[j]) {
			a[m] = a2[j++];
		} else {
			a[m] = a1[i++];
		}
		m++;
	}
	while (i < n1 && k < n3) {
		if (a1[i] > a3[k]) {
			a[m] = a3[k++];
		} else {
			a[m] = a1[i++];
		}
		m++;
	}
	while (j < n2 && k < n3) {
		if (a2[j] > a3[k]) {
			a[m] = a3[k];
		} else {
			a[m] = a2[j++];
		}
		m++;
	}
	while (i < n1) {
		a[m++] = a1[i++];
	}
	while (j < n2) {
		a[m++] = a2[j++];
	}
	while (k < n3) {
		a[m++] = a3[k++];
	}
	return a;
}

int* generateRandomArray (int n, int whichProcess) {
	int* a = (int *) malloc (n * sizeof (int ));
	int i;
	int randomNumbers[3];
	for (int i = 0; i < n; i++) {
		randomNumbers[0] = (rand() % MAX_NUM) + 1;
		randomNumbers[1] = (rand() % MAX_NUM) + 1;
		randomNumbers[2] = (rand() % MAX_NUM) + 1;
		a[i] = randomNumbers[whichProcess];
		// printf ("%3d\t%3d\t%3d\t%3d\t%3d\n", whichProcess, randomNumbers[0], randomNumbers[1], randomNumbers[2], a[i]);
	}
	return a;
}

int main () {

	srand (time (NULL));
	
	int pipe1[2], pipe2[2], pipe3[2];
	int status;
	char buf[BUF_SIZE];
	int count;
	
	status = pipe (pipe1);
	if (status == -1) {
		// error creating pipe
		perror ("Error creating pipe");
		exit (1);
	}
	status = fork ();
	if (status == -1) {
		// error creating process
		perror ("Error creating process");
		exit (2);
	} else if (status == 0) {
		// this is child
		// generate random numbers and send through pipe1
		// close (pipe1[0]);
		int* arr = generateRandomArray(TOTAL_INTS, 0);
		
		mergeSort (arr, 0, TOTAL_INTS - 1);
		close (pipe1[0]);
		write (pipe1[1], arr, TOTAL_INTS * sizeof (int));
		free (arr);
		close (pipe1[1]);
	} else {
		// this is parent
		// create another pipe and process
		status = pipe (pipe2);
		if (status == -1) {
			// error creating pipe
			perror ("Error creating pipe");
			exit (3);
		}
		status = fork ();
		if (status == -1) {
			// error creating process
			perror ("Error creating process");
			exit (4);
		} else if (status == 0) {
			// this is child
			// generate random numbers and send through pipe1
			// close (pipe2[0]);
			int* arr = generateRandomArray(TOTAL_INTS, 1);
			
			mergeSort (arr, 0, TOTAL_INTS - 1);
			close (pipe2[0]);
			write (pipe2[1], arr, TOTAL_INTS * sizeof (int));
			free (arr);
			close (pipe2[1]);
		} else {
			// this is parent
			// create another pipe and process
			status = pipe (pipe3);
			if (status == -1) {
				// error creating pipe
				perror ("Error creating pipe");
				exit (5);
			}
			status = fork ();
			if (status == -1) {
				// error creating process
				perror ("Error creating process");
				exit (6);
			} else if (status == 0) {
				// this is child
				// generate random numbers and send through pipe1
				// close (pipe3[0]);
				int* arr = generateRandomArray(TOTAL_INTS, 2);
				
				mergeSort (arr, 0, TOTAL_INTS - 1);
				close (pipe3[0]);
				write (pipe3[1], arr, TOTAL_INTS * sizeof (int));
				free (arr);
				close (pipe3[1]);
			} else {
				// this is parent
				// get data from three pipes
				close (pipe1[1]);
				close (pipe2[1]);
				close (pipe3[1]);
				int arr1[TOTAL_INTS], arr2[TOTAL_INTS], arr3[TOTAL_INTS];
				// int arr[3 * TOTAL_INTS];
				for (count = 0; count < 3; ) {
					if (read (pipe1[0], arr1, TOTAL_INTS * sizeof (int)) > 0) {
						// printf ("From process 1 : %s\n", buf);
						count++;
					}
					if (read (pipe2[0], arr2, TOTAL_INTS * sizeof (int)) > 0) {
						// printf ("From process 2 : %s\n", buf);
						count++;
					}
					if (read (pipe3[0], arr3, TOTAL_INTS * sizeof (int)) > 0) {
						// printf ("From process 3 : %s\n", buf);
						count++;
					}
				}
				int* arr = merge2 (arr1, arr2, arr3, TOTAL_INTS, TOTAL_INTS, TOTAL_INTS);
				printf ("\nReceived data in sorted order is:\n");
				for (count = 0; count < 3 * TOTAL_INTS; count++) {
					printf ("arr[%3d] = %7d\n", count, arr[count]);
				}
				free (arr);
				close (pipe1[0]);
				close (pipe2[0]);
				close (pipe3[0]);
			}
		}
	}
	
	return 0;
}

