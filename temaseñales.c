#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main(void)
{
 struct sigaction act;

 act.sa_handler= SIG_IGN; /* Ignora la señal */
 act.sa_flags= 0; /* Ninguna accion especial */
 sigemptyset(&act.sa_mask); /* Ninguna señal bloqueada */

 sigaction(SIGINT, &act, NULL);

 sleep(10);

 return 0;
}