#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <sys/msg.h> 
#include <string.h> 
//ranking victorias más rapidas
#define MAX_SEND_SIZE 15
struct mymsgbuf{ 
   long mtype; 
   char mtext[MAX_SEND_SIZE]; 
}; 


int leer_msg(int qid,long type,struct mymsgbuf *qbuf); 


int leer_msg(int qid,long type,struct mymsgbuf *qbuf) 
{ 
   int resultado;
   
   resultado=msgrcv(qid,qbuf,MAX_SEND_SIZE,type,0); 
    
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
  
  while(1)
  {
          tipo = 1;
          printf("Leyendo tipo1...\n"); 
          leer_msg(msgqueue_id,tipo,&qbuffer); 
          printf("Tipo: %ld Texto:%s \n",qbuffer.mtype,qbuffer.mtext);
          printf("Leyendo tipo1...\n"); 
          tipo = 2;
          leer_msg(msgqueue_id,tipo,&qbuffer2); 
          printf("Tipo: %ld Texto:%s \n",qbuffer2.mtype,qbuffer2.mtext);

  }
  


       }
return 0;

}
