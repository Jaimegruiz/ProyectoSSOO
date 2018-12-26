#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for execlp
 
int main () {
        pid_t x;      // a special kind of int
        char kil[20] = "kill -s 9 ";
 
        x = fork();   /* now there's actually two "x"s:
if fork succeeds, "x" to the CHILD PROCESS is the return value of fork (0)
and "x" to the PARENT PROCESS is the actual system pid of the child process.*/
         
        if (x < 0) {  // just in case fork fails 
                puts("fork failure");
                exit(-1);
        }   
        else if (x == 0) { // therefore this block will be the child process 
                execlp("mpg123", "mpg123", "-q", "my.mp3", (char*)0); 
        }                   // see GNU docs, "system" also works                
        else {  printf("from parent: mpg123 is pid %d\nENTER to quit\n", x);
                sprintf(kil,"%s%d",kil,x);
                getchar();  // wait for user input
                system(kil);
                printf("All ");
        }       
        printf("done.\n");
        exit(0);
}