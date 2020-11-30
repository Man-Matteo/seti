/* funzioni da implementare
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

int main() {

for (;;) {

   //cartella corrente
   mypwd();

   //lettura stdin
   char *a = NULL;
   size_t alen = 0;
   ssize_t alineSize = 0;
   alineSize = getline(&a, &alen, stdin);

   //divisione dei token in array[]
   const char s[2] = "|";
   char *token;
   char *array[alineSize];

   token = strtok(a, s);

   int index = 0;
   while( token != NULL ) {
       printf( " %s\n", token );
       array[index++] = token;
       token = strtok(NULL, s);
   }

  for (int i = 0; i < index; i++) printf("%s\n", array[i]);

}
}
