#include <sys/stat.h> /* struct stat y fstat */
#include <sys/mman.h> /* mmap */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_SEND_SIZE 16
#define TOP3	3
int main(void)
{

	int fdo;
	char *org;
	//char * aux;
	//char * aux2;
	char nuevo_rank[100];
	struct stat bstat;
	char primero[MAX_SEND_SIZE] = "Vacante";
    char segundo[MAX_SEND_SIZE] = "Vacante";
    char tercero[MAX_SEND_SIZE] = "Vacante";
    char rank1[MAX_SEND_SIZE];
    char rank2[MAX_SEND_SIZE];
    char rank3[MAX_SEND_SIZE];
    double rank[TOP3] = {1000000,1000000,1000000};


	if ((fdo=open("guardado.txt", O_RDWR))<0)
	{
		perror("No puede abrirse el fichero origen");
	}
	else if (fstat(fdo, &bstat)<0)
 	{
 	perror("Error en fstat del fichero origen");
 	}
 	else if ((org=(char *)mmap(0, bstat.st_size,PROT_READ|PROT_WRITE,MAP_SHARED, fdo, 0)) == MAP_FAILED)
 	{

 		perror("Error en la proyeccion del fichero origen");
 	}	
 	else//no error
 	{
 		close(fdo);

 		sscanf(org, "%s %s %s %lf %lf %lf", primero,segundo,tercero,&rank[0],&rank[1],&rank[2]);
 		

 		printf("\n");
 		printf("\t 1. %s \t %lf segundos \n\n",primero,rank[0]);
        printf("\t 2. %s \t %lf segundos \n\n",segundo,rank[1]);
        printf("\t 3. %s \t %lf segundos \n\n",tercero,rank[2]);
        printf("\n");
        //printf("%ld\n", bstat.st_size);
        //ahora probamos a escribir el nuevo ranking al terminar una buena partida
        //nuevo_rank = primero + segundo + tercero + rank[0] + rank[1] + rank[2];
        strcpy(primero, "yoli");
        strcpy(segundo, "nicolasin");
        rank[0] = 15.6;
        rank[1] = 34.56;
        snprintf(rank1, MAX_SEND_SIZE+1, "%lf", rank[0]);
        snprintf(rank2, MAX_SEND_SIZE+1, "%lf", rank[1]);
        snprintf(rank3, MAX_SEND_SIZE+1, "%lf", rank[2]);
        strcpy(nuevo_rank, primero);
        strcat(nuevo_rank, " ");
        strcat(nuevo_rank, segundo);
        strcat(nuevo_rank, " ");
        strcat(nuevo_rank, tercero);
        strcat(nuevo_rank, " ");
        strcat(nuevo_rank, rank1);
        strcat(nuevo_rank, " ");
        strcat(nuevo_rank, rank2);
        strcat(nuevo_rank, " ");
        strcat(nuevo_rank, rank3);
		printf("%s\n",nuevo_rank);

		//lo escribimos en el fichero
		/*
		aux = org;
		aux2 = nuevo_rank;
		for (int i=0; i<200; i++)
		{
			*aux++=*aux2++;
		}*/
		strcpy(org,nuevo_rank);

 		if (munmap(org, bstat.st_size)==-1)
 		{
 			perror("Error en unmap");
 		}

 	

 	}
  












}



