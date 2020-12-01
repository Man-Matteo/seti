#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define __USE_BSD
#include <limits.h>

void mypwd(char* cwd) {
    getcwd(cwd, PATH_MAX);
}

void mycd(char* cwd, char* argument) {

    if (strcmp(argument, "..") == 0) {
        printf("Errore .. non disponibile\n");
        _exit;
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


        if (strcmp(blank[0], "cd") == 0) {

            if (index > 2) {
                printf("Errore troppi argomenti per cd\n");
                continue;
            }
           mycd(cwd, blank[1]);
         }

       }
   }


        /*for (scorro ogni carattere) {
            if (trovo "$")
              chiamo funzione $ e sostituisco comando
            if (trovo "<" || trovo ">" )
              reindirizzo input/output
            if (trovo "|")
              STDOUT comando 1 = STDIN comando 2
        }

          .....

          for (ogni "parola token") {
            if (comando 1)
              chiamo funzione 1
            if (comando 2)
              chiamo funzione 2

          .....
          }
        */
