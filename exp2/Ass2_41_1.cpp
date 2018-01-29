#include <bits/stdc++.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ios>
#include <limits>

using namespace std;

#define msize 100

#define INTERNAL 0
#define EXTERNAL 1
#define INPUT_FROM_FILE 2
#define OUTPUT_TO_FILE 3
#define BACKGROUND 4
#define PIPE_MODE 5
#define QUIT 6
#define SEP_CHAR '|'

void str_to_words (string, string[]);
void execute_pr (char **argv);
void execute_pr2 (char **argv);
void execute_pr_inp_file (char **, char *);
void execute_pr_out_file (char **, char *);

int getNumberOfSeperatingCharacters (string s) {
	int counter = 0;
	int n = s.length ();
	for (int i = 0; i < n; i++) {
		if (s[i] == SEP_CHAR) {
			counter++;
		}
	}
	return counter;
}

int showMenu () {
	// getchar ();
	cin.sync();
	cout << "----------------------------------------------" << endl;
	cout << "[A] : Run an internal command" << endl;
	cout << "[B] : Run an external command" << endl;
	cout << "[C] : Run an external command by redirecting standard input from a file" << endl;
	cout << "[D] : Run an external command by redirecting standard output to a file" << endl;
	cout << "[E] : Run an external command in the background" << endl;
	cout << "[F] : Run several external commands in the pipe mode" << endl;
	cout << "[G] : Quit the shell" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Select one option [A/B/C/D/E/F/G] (Default is A) : ";
	char c;
	cin >> c;
	// cout << "Choice = " << c << endl;
	return (int ) (c - 'A');
}

void execute_external () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	string strWords[msize];
	str_to_words(cmd,strWords);
	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	char *argv[rc+1];
	for (int i = 0; i < rc; ++i) {
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	if (strWords[0]=="quit")
		exit(0);

    execute_pr(argv);
}

void execute_internal () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	string strWords[msize];
	str_to_words(cmd,strWords);
	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	char *argv[rc+1];
	for (int i = 0; i < rc; ++i) {
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	if (strWords[0]=="quit")
		exit(0);

	if (strcmp (argv[0], "mkdir") == 0) {
		// mkdir (argv[1], 0777)
		if (mkdir (argv[1], 0777) == 1) {
			// Error
			cout << "Error : mkdir" << endl;
		}
	} else if (strcmp (argv[0], "cd") == 0) {
		// chdir (argv[1])
		if (chdir (argv[1]) == 1) {
			// Error
			cout << "Error : cd" << endl;
		}
	} else if (strcmp (argv[0], "rmdir") == 0) {
		// rmdir (argv[1])
		if (rmdir (argv[1]) == 1) {
			// Error
			cout << "Error : rmdir" << endl;
		}
	} else {
		cout << argv[0] << " is not an internal command." << endl;
	}
	return;
}

void execute_input_from_file () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	string strWords[msize];
	str_to_words(cmd,strWords);
	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	int l = strWords[rc - 1].length ();
	cout << "l = " << l << endl;
	cout << "filename1:" << strWords[rc -1] << ":\n";
	char *filename = new char[l + 1];
	for (int x = 0; x < l; x++) {
		filename[x] = strWords[rc - 1][x];
	}
	filename[l] = '\0';
	cout << "l = " << l << endl;
	cout << "filename1:" << strWords[rc -1] << ":\n";
	rc--;
	while (strWords[rc - 1] == "<") {
		rc--;
	}
	char *argv[rc+1];
	for (int i = 0; i < rc; ++i) {
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	if (strWords[0]=="quit")
		exit(0);
    execute_pr_inp_file(argv, filename);
    // open (1);
	return;
}

void execute_output_to_file () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	string strWords[msize];
	str_to_words(cmd,strWords);
	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	int l = strWords[rc - 1].length ();
	cout << "l = " << l << endl;
	cout << "filename1:" << strWords[rc -1] << ":\n";
	char *filename = new char[l + 1];
	for (int x = 0; x < l; x++) {
		filename[x] = strWords[rc - 1][x];
	}
	filename[l] = '\0';
	cout << "filename2:" << filename << ":\n";
	rc--;
	while (strWords[rc - 1] == ">") {
		rc--;
	}
	char *argv[rc+1];
	for (int i = 0; i < rc; ++i) {
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	if (strWords[0]=="quit")
		exit(0);
	execute_pr_out_file (argv, filename);
    // open (1);
	return;
}

void execute_pipe_mode () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	int numPipes = getNumberOfSeperatingCharacters (cmd);
	vector < string > strs;
	int j = 0;
	for (int i = 0; i <= numPipes; i++) {
		string s = "";
		while (j < cmd.length () && (cmd[j] == ' ' || cmd[j] == '\t')) {
			j++;
		}
		while (j < cmd.length ()) {
			if (cmd[j] == SEP_CHAR) {
				j++;
				break;
			} else if (cmd[j] == ' ' || cmd[j] == '\t') {
				if (j < cmd.length() - 1 && cmd[j + 1] != ' ' && cmd[j + 1] != '\t' && cmd[j + 1] != SEP_CHAR) {
					s += cmd[j++];
				} else {
					j++;
				}
			} else {
				s += cmd[j++];
			}
		}
		strs.push_back (s);
	}
	// for (int i = 0; i <= numPipes; i++) {
	// 	cout << "strs[" << i << "] = --" << strs[i] << "--\n";
	// }
	if (numPipes == 0 && strs[0] == "") {
		return;
	}
	int pipes[numPipes][2];
	pid_t child;
	int status;
	for (int i = 0; i <= numPipes; i++) {
		
		if ((child = fork ()) < 0) {
			cout << "*** ERROR: Unable to fork child" << endl;
		} else if (child == 0) {
			// child process
			// execute first command
			// put input of pipe here

			// convert string to char **
			string strWords[msize];
			str_to_words(strs[i],strWords);
			for (int ii = 0; ii < msize; ++ii)
			{
				if(strWords[ii]==""){
					rc=ii;
					break;
				}
			}
			char *argv[rc+1];
			for (int ii = 0; ii < rc; ++ii) {
				char* name = new char[20];
				for (int j = 0; j < strWords[ii].length(); j++) {
					name[j] = strWords[ii][j];
				}
				name[strWords[ii].length()] = '\0';
				argv[ii] = name;
			}
			argv[rc] = '\0';
			if (strWords[0]=="quit")
				exit(0);
				
			if (i != 0) {
				dup2 (pipes[i - 1][0], 0);
			}
			if (i != numPipes) {
				dup2 (pipes[i][1], 1);
			}
			// close all pipes
			for (int j = 0; j < numPipes; j++) {
				close (pipes[j][0]);
				close (pipes[j][1]);
			}

		    // execute_pr(argv);
			execvp (argv[0], argv);

		} else {
			// parent process
			// if (i == numPipes) {
			// 	while (wait (&status) != child)
			// 	;
			// }
			// while (wait(&status) != child)      /* wait for completion  */
            //     ;
		}
	}
	// close all pipes
	for (int j = 0; j < numPipes; j++) {
		close (pipes[j][0]);
		close (pipes[j][1]);
	}
	for (int i = 0; i <= numPipes; i++) {
		wait (&status);
	}
	return;
}

void execute_background () {
	cout<<"@Group41:";
	string cmd;
	int rc;
	getchar ();
	getline(cin,cmd);
	string strWords[msize];
	str_to_words(cmd,strWords);
	for (int i = 0; i < msize; ++i)
	{
		if(strWords[i]==""){
			rc=i;
			break;
		}
	}
	while (strWords[rc - 1] == "&") {
		rc--;
	}
	char *argv[rc+1];
	for (int i = 0; i < rc; ++i) {
		char* name = new char[20];
		for (int j = 0; j < strWords[i].length(); j++) {
			name[j] = strWords[i][j];
		}
		name[strWords[i].length()] = '\0';
		argv[i] = name;
	}
	argv[rc] = '\0';
	if (strWords[0]=="quit")
		exit(0);

    execute_pr2(argv);
}


void str_to_words (string cmd, string strWords[]) {
 	int counter = 0;
 	for (int i = 0; i < cmd.length(); i++) {
		if (cmd[i] == ' ')
		    counter++;
		else
		    strWords[counter] += cmd[i];
	}
}

void  execute_pr (char **argv)
{
     pid_t  prid;
     int    status;

     if ((prid = fork()) < 0) {     /* fork child process */
          cout << "*****ERROR: Forking Child Failed*****" << endl;
          exit (1);
     } else if (prid == 0) {          /* for the child process:         */
          if (execvp (*argv,argv) < 0) {     /* run command  */
               cout << "*****ERROR: EXEC FAILED*****" << endl;
               exit (1);
          }
     } else {                                  /* for parent:  */
          while (wait(&status) != prid)      /* wait for completion  */
               ;
          // cin.ignore(numeric_limits<streamsize>::max(),'\n');
     }
}

void  execute_pr2 (char **argv)
{
     pid_t  prid;
     int    status;

     if ((prid = fork()) < 0) {     /* fork child process */
          cout << "*****ERROR: Forking Child Failed*****" << endl;
          exit (1);
     } else if (prid == 0) {          /* for the child process:         */
          if (execvp (*argv,argv) < 0) {     /* run command  */
               cout << "*****ERROR: EXEC FAILED*****" << endl;
               exit (1);
          }
     } else {                                  /* for parent:  */
          // while (wait(&status) != prid)      /* wait for completion  */
          //      ;
     }
}

void  execute_pr_inp_file (char **argv, char* filename)
{
     pid_t  prid;
     int    status;

     if ((prid = fork()) < 0) {     /* fork child process */
          cout << "*****ERROR: Forking Child Failed*****" << endl;
          exit (1);
     } else if (prid == 0) {          /* for the child process:         */
		 int in = open (filename, O_RDONLY);
		 cout << "filename:" << filename << ":" << endl;
		 dup2 (in, 0);
		 close (in);
      if (execvp (*argv,argv) < 0) {     /* run command  */
           cout << "*****ERROR: EXEC FAILED*****" << endl;
           exit (1);
      }
     } else {                                  /* for parent:  */
          while (wait(&status) != prid)      /* wait for completion  */
                ;
     }
}

void  execute_pr_out_file (char **argv, char* filename)
{
     pid_t  prid;
     int    status;

     if ((prid = fork()) < 0) {     /* fork child process */
          cout << "*****ERROR: Forking Child Failed*****" << endl;
          exit (1);
     } else if (prid == 0) {          /* for the child process:         */
		 int out = open (filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		 cout << "filename:" << filename << ":" << endl;
		 dup2 (out, 1);
		 close (out);
      if (execvp (*argv,argv) < 0) {     /* run command  */
           cout << "*****ERROR: EXEC FAILED*****" << endl;
           exit (1);
      }
     } else {                                  /* for parent:  */
          while (wait(&status) != prid)      /* wait for completion  */
                ;
     }
}

int main(){
	while(1){

		int choice = showMenu ();
		// cout << "Choice = " << choice;
		switch (choice) {
			case INTERNAL:
				execute_internal ();
				break;
			case EXTERNAL:
				execute_external ();
				break;
			case INPUT_FROM_FILE:
				execute_input_from_file ();
				break;
			case OUTPUT_TO_FILE:
				execute_output_to_file ();
				break;
			case BACKGROUND:
				execute_background ();
				break;
			case PIPE_MODE:
				execute_pipe_mode ();
				break;
			case QUIT:
				exit (1);
			// default:
				// execute_internal ();
		}
	/*
		cout<<"@Group41:";
		string cmd;
		int rc;
		getline(cin,cmd);
		string strWords[msize];
		str_to_words(cmd,strWords);
		for (int i = 0; i < msize; ++i)
		{
			if(strWords[i]==""){
				rc=i;
				break;
			}
		}
		char *argv[rc+1];
		for (int i = 0; i < rc; ++i) {
			char* name = new char[20];
			for (int j = 0; j < strWords[i].length(); j++) {
				name[j] = strWords[i][j];
			}
			name[strWords[i].length()] = '\0';
			argv[i] = name;
		}
		argv[rc] = '\0';
		if (strWords[0]=="quit")
			exit(0);

        execute_pr(argv);
        */
	}
	return 0;
}
