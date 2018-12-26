#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMERO_PALABRAS 6
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
int main(void){

	printf("Inicio\n");

  	sem_t *semH = NULL;
  	//int num = 0;
	key_t clave;
	int shmid = 0;
	struct Palabras * palabras_ptr;
	char palabra_enjuego[LONGITUD_MAX];
	
	//char array2D[NUMERO_PALABRAS,LONGITUD_MAX];
	clave=ftok(".",'X');
		   
	/* Abrimos los semaforos */
	semH = sem_open("palabra",0);
	if(semH != NULL)
	{
		printf("Semáforo abierto correctamente\n");
		 if((shmid=shmget(clave,TAM,0)) !=-1)
		 {
		 	printf("Acceso exitoso a la MC\n");

		 	palabras_ptr = shmat(shmid, NULL, 0);
		 	
			
		 	sem_wait(semH);
		 	printf("Acceso exitoso al semaforo\n");

		 	int pos = palabras_ptr->posicion;
		 	switch(pos){

		 		case 0:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra1);
		 		break;
		 		case 1:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra2);
		 		break;
		 		case 2:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra3);
		 		break;
		 		case 3:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra4);
		 		break;
		 		case 4:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra5);
		 		break;
		 		case 5:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra6);
		 		break;
		 		case 6:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra7);
		 		break;
		 		case 7:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra8);
		 		break;
		 		case 8:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra9);
		 		break;
		 		case 9:
		 		strcpy(palabra_enjuego, palabras_ptr->palabra10);
		 		break;
		 		default:
		 			printf("Err");

		 	}
		 	palabras_ptr->posicion = (palabras_ptr->posicion +1)%10;
		 	printf("%s\n",palabra_enjuego);
		 	sem_post(semH);
		 	printf("Salgo del semaforo\n");
		 	shmdt(palabras_ptr);
		 	printf("MC detached\n");
		    sem_close(semH);
		    printf("Cierro el semaforo\n");
		 }else
		 {
		 	printf("Error al acceder a la MC\n");
		 }

	}else
	{
		printf("Error al abrir el Semáforo\n");
	}	
	  

	
	return 0;
 
}
