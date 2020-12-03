#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void mypwd(char* cwd) {
    getcwd(cwd, PATH_MAX);
}

void mycd(char* cwd, char* argument) {

   argument[strcspn(argument, "\n")] = 0;
    if (strcmp(argument, "..") == 0 || strcmp(argument, "") == 0 ) {
        printf("Errore .. non disponibile\n");
       return;
    }

    strcat(cwd,"/");
    strcat(cwd, argument);
    cwd[strcspn(cwd, "\n")] = 0;

}

int mytokenizer(char* a, char* s, char** array) {

    char *token;
    token = strtok(a, s);

    int index = 0;
    while( token != NULL ) {
        array[index] = token;
        index++;
        token = strtok(NULL, s);
    }

    return index;
}

void myexecargument(char* command, char* argument, char* cwd, int index) {
    int pid = fork(), execres, nfd, status; /* create a new process */

    	command[strcspn(command, "\n")] = 0;
    	char cmd[50] = "/bin/";
    	strcat(cmd, command);


    	if(pid<0) perror("fork failed");

    	if(pid==0){
	    	nfd=open(cwd, O_CREAT | O_RDWR);
	    	dup2(nfd, 1);
	    	close(nfd);


	    if (index == 1) {
	        execres = execl(cmd, cmd, NULL);
	    }
	    else {
			 argument[strcspn(argument, "\n")] = 0;
			 execres=execl(cmd, cmd, argument, NULL);
		 }

	    if(execres<0) perror("execl failed");


    	}

	waitpid(pid, &status, 0);
}

int main() {


    char cwd[PATH_MAX];
    mypwd(cwd);

    for (;;) {

        //cartella corrente
        printf("%s $ ", cwd);

        //lettura stdin
        char *a = NULL;
        size_t alen = 0;
        ssize_t alineSize = 0;
        alineSize = getline(&a, &alen, stdin);

        //divisione dei token per spazi
        char* blank[alineSize];
        int index = mytokenizer(a, " ", blank);


        if (strcmp(blank[0], "\n") == 0) continue;

        if (strcmp(blank[0], "cd") == 0) {
            if (index > 2) {
                printf("Errore troppi argomenti per cd\n");
                continue;
            }
           mycd(cwd, blank[1]);
         } else {
            myexecargument(blank[0], blank[1], cwd, index);
         }
    }
}
