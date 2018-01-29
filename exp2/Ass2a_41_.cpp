#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

#define MAX_SIZE 5

struct _item {
	int value;
};

typedef _item item;

item buffer[MAX_SIZE];
int in = 0;
int out = 0;

int main (void) {
	int np, nc;
	cin >> np >> nc;
	
	for (int i = 0; i < np; i++) {
		if (fork () == 0) {
			srand (getpid ());
			// child process (producer[i])
			while (true) {
				// generate random number
				int rand_num = rand ();
				int s = rand() % 100;
				item next_produced;
				next_produced.value = rand_num;
				cout << "Producer " << i << ": " << next_produced.value << ", time: " << time (NULL) << endl;
				sleep (s);
				while ((in + 1) % MAX_SIZE == out);
				buffer[in] = next_produced;
				in = (in + 1) % MAX_SIZE;
			}
		}
	}
	
	for (int i = 0; i < nc; i++) {
		if (fork () == 0) {
			// child process (consumer[i])
			item next_consumed;
			while (true) {
				int s = rand () % 100;
				sleep (s);
				while (in == out);
				next_consumed = buffer[out];
				out = (out + 1) % MAX_SIZE;
				cout << "Consumer " << i << ": " << next_consumed.value << ", time: " << time (NULL) << endl;
			}
		}
	}
	
	return 0;
}

