//NOT WORKING 

/*  funzioni da implementare
    cd
    > / <
    grep
    |
    cat
    ls / ls -l

    cosa ci serve:
    funzione che legge da input e divide i comandi

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int PATH_MAX = 4096; //lib limits.h

void mypwd() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf(" %s $ ", cwd);
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

void commandfinder (char* array, int info) {

    for (int i = 0; i < info; i++) {
      if (array == "cd" || array == "grep" || array == "ls" || array == "cat" || array == "wc")
        printf("OK!!\n");
      else
        printf("NO!!\n");
    }
  }

int main() {

    for (;;) {

        //cartella corrente
        mypwd();

        //lettura stdin
        char *a = NULL;
        size_t alen = 0;
        ssize_t alineSize = 0;
        alineSize = getline(&a, &alen, stdin);



        //divisione dei token per spazi
        char* tokenspazio[alineSize];
        int index = mytokenizer(a, " ", tokenspazio);

        for (int i = 0; i < index; i++) {

            commandfinder(tokenspazio[i], index);
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
