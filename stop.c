#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>

#include <sys/msg.h> 
#define NUMERO_PALABRAS 10
#define LONGITUD_MAX 15
#define TAM 200
struct Palabras
{
    char palabra1[LONGITUD_MAX];
    char palabra2[LONGITUD_MAX];
    char palabra3[LONGITUD_MAX];
    char palabra4[LONGITUD_MAX];
    char palabra5[LONGITUD_MAX];
    char palabra6[LONGITUD_MAX];
    char palabra7[LONGITUD_MAX];
    char palabra8[LONGITUD_MAX];
    char palabra9[LONGITUD_MAX];
    char palabra10[LONGITUD_MAX];

    int posicion;
    
};

int main(){
  int shmid = 0;
  int msgid = 0;
  
  key_t clave;
  clave=ftok(".",'X');

  /* Destruimos los semaforos */
  sem_unlink("palabra");
 
  
  /* Si la memoria compartida existia, la borramos */
  if ((shmid = shmget(clave,TAM,0)) != -1){
    shmctl(shmid,IPC_RMID,NULL);
	  printf("Segmento de memoria compartida eliminado correctamente.\n");
  }
  /* Si la cola existia, la borramos */
  if ((msgid = msgget(clave,0)) != -1){
    shmctl(msgid,IPC_RMID,NULL);
    printf("Cola eliminada correctamente.\n");
  }

  
  return 0;
}