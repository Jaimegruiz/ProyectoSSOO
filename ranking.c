#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <sys/msg.h> 
#include <string.h> 
//ranking victorias más rapidas
#define MAX_SEND_SIZE 16
#define TOP3 3
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
   char primero[MAX_SEND_SIZE] = "Vacante";
   char segundo[MAX_SEND_SIZE] = "Vacante";
   char tercero[MAX_SEND_SIZE] = "Vacante";
   double rank[TOP3] = {1000000,1000000,1000000};
   double nuevo_valor;
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
          printf("Leyendo nombre...\n"); 
          leer_msg(msgqueue_id,tipo,&qbuffer); 
          printf("Tipo: %ld Texto:%s \n",qbuffer.mtype,qbuffer.mtext);
          printf("Leyendo tiempo...\n"); 
          tipo = 2; 
          leer_msg(msgqueue_id,tipo,&qbuffer2); 
          printf("Tipo: %ld Texto:%s \n",qbuffer2.mtype,qbuffer2.mtext);

          
         

          sscanf(qbuffer2.mtext, "%lf", &nuevo_valor);

          printf("Nuevo valor: %lf", nuevo_valor);

          if (nuevo_valor < rank[0])
          {
            strcpy(tercero, segundo);
            strcpy(segundo, primero);
            strcpy(primero, qbuffer.mtext);
            rank[2]= rank[1];
            rank[1]= rank [0];
            rank[0] = nuevo_valor;
          }else if(nuevo_valor < rank[1]){
            strcpy(tercero, segundo);
            strcpy(segundo, qbuffer.mtext);
            rank[2]= rank[1];
            rank[1] = nuevo_valor;

          }else if(nuevo_valor < rank [2]){
            strcpy(tercero, qbuffer.mtext);
            rank[2] = nuevo_valor;
          }

          printf("\n");
          printf("\n");
          printf("-------------TOP 3 MEJORES JUGADORES-------------\n\n");
          printf("\t 1. %s \t %lf segundos \n\n",primero,rank[0]);
          printf("\t 2. %s \t %lf segundos \n\n",segundo,rank[1]);
          printf("\t 3. %s \t %lf segundos \n\n",tercero,rank[2]);


  }
  


       }
return 0;

}
