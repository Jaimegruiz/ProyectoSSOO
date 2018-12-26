#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/msg.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>

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
  /* Inicializamos las variables */
  sem_t *semH = NULL;
 
  struct Palabras * palabras_ptr;
  int shmid = 0;
  key_t clave;
  clave=ftok(".",'X');
  int msg;
  //lista palabras memoria cmpartida
  
  
  /* Creamos los semaforos */
  semH = sem_open("palabra",O_CREAT,0600,1);

  if ((msg = msgget(clave,IPC_CREAT|IPC_EXCL|0600)) == -1)
  {
    printf("Error al crear cola\n");
  }
  else{
    printf("Cola creada\n");
  }
  


  if (semH != NULL){
    sem_close(semH);
  }
  
  
  /* Creamos la zona de memoria compartida */
  if ((shmid = shmget(clave, TAM, IPC_CREAT|IPC_EXCL|0600)) != -1){
	  
	  printf("Segmento de memoria compartida creado correctamente.\n");
	  //printf("%s\n",strs[0]);
	  /* Inicializamos el buffer */
	  palabras_ptr = shmat(shmid, NULL, 0);


    strcpy(palabras_ptr->palabra1, "perro");
    strcpy(palabras_ptr->palabra2, "gato");
    strcpy(palabras_ptr->palabra3, "elefante");
    strcpy(palabras_ptr->palabra4, "cocodrilo");
    strcpy(palabras_ptr->palabra5, "jirafa");
    strcpy(palabras_ptr->palabra6, "avestruz");
    strcpy(palabras_ptr->palabra7, "ferrari");
    strcpy(palabras_ptr->palabra8, "prueba");
    strcpy(palabras_ptr->palabra9, "langostinos");
    strcpy(palabras_ptr->palabra10, "estupefacto");
    
	  palabras_ptr->posicion = 0;
	  
	  
	 
    printf("%s\n",palabras_ptr->palabra1 );
    printf("%s\n",palabras_ptr->palabra2 );
    printf("%s\n",palabras_ptr->palabra3 );
    printf("%s\n",palabras_ptr->palabra4 );
    printf("%s\n",palabras_ptr->palabra5 );
    printf("%s\n",palabras_ptr->palabra6 );
    printf("%s\n",palabras_ptr->palabra7 );
    printf("%s\n",palabras_ptr->palabra8 );
    printf("%s\n",palabras_ptr->palabra9 );
    printf("%s\n",palabras_ptr->palabra10 );
	  shmdt(palabras_ptr);
	  
	  
  }else{
	  printf("ERROR: El segmento de memoria no se pudo crear, puede que ya este creado.\n");
  }
  
  return 0;
}
