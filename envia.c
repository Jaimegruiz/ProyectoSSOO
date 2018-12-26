#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <sys/msg.h> 
#include <string.h> 
#include <unistd.h>

#define MAX_SEND_SIZE 15
struct mymsgbuf{ 
   long mtype; 
   char mtext[MAX_SEND_SIZE]; 
}; 

int escr_msg(int qid,struct mymsgbuf *qbuf); 


int escr_msg(int qid,struct mymsgbuf *qbuf) 
{ 
   int resultado;
   
   resultado=msgsnd(qid,qbuf,MAX_SEND_SIZE,0);
      
   return (resultado);

} 

 

int main() 
{ 
   key_t clave; 
   int msgqueue_id; 
   long tipo; 
   struct mymsgbuf qbuffer; 
   struct mymsgbuf qbuffer2; 
   clave=ftok(".",'X');
   if ((msgqueue_id=msgget(clave,IPC_CREAT|0600))==-1) 
      { 
         printf("Error al iniciar la cola\n"); 
      } 

   else 
      { 
	tipo = 1;
	
	for(int i=0; i<5; i++)
	{
    //enviamos el nombre del jugador
		tipo = 1;
		printf("Enviando tipo 1...\n"); 
        	qbuffer.mtype = tipo; 
       	 	strncpy(qbuffer.mtext,"jaime",MAX_SEND_SIZE-1);
        	qbuffer.mtext[MAX_SEND_SIZE-1]='\0';
		escr_msg(msgqueue_id,&qbuffer);
  sleep(1);
  //enviamos el tiempo en segundos del jugador
    tipo = 2;
    printf("Enviando tipo 2...\n"); 
          qbuffer2.mtype = tipo; 
          strncpy(qbuffer2.mtext,"43.2",MAX_SEND_SIZE-1);
          qbuffer2.mtext[MAX_SEND_SIZE-1]='\0';
    escr_msg(msgqueue_id,&qbuffer2);
    sleep(1);


	}
	


       }
return 0;

}
