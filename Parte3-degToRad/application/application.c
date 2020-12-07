#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"

#define TAM 360

static volatile float a[TAM];

static volatile int flag = 0;
static volatile int flag2 = 0;
static volatile int vetorCriado = 0;
static volatile int flagPrint = 0;
static volatile int done = 0;

float deg2rad(int deg)
{
    return ((deg)*3.14159265359 / 180);
}

int cpu0(int id)
{

    while (!vetorCriado) //Fica preso enquanto nao criou o vetor
    {
    }
    int i;
    printf("Iniciando cpu0\n");
    for (i = 0; i < TAM/2 ; i++)
    {
        a[i] = deg2rad(i);
    }

    flag = 1; //Parte 1 finalizada

    while (!flag2) //Fica preso enquanto parte 2 nao acabou
    {
    }

    flagPrint++;  //Parte 1 pronta para printar
    while (!done) //Espera o print acabar
    {
    }
    printf("Acabou cpu0\n");

    return 1;
}

int cpu1(int id)
{
    while (!vetorCriado) //F ica preso enquanto nao criou o vetor
    {
    }
    printf("Iniciando cpu1\n");
    int j;
    for (j = TAM / 2; j <= TAM; j++)
    {
        a[j] = deg2rad(j);
    }

    flag2 = 1; //Parte 2 finalizada

    while (!flag) //Fica preso enquanto parte 1 nao acabou
    {
    }
    flagPrint++;  //Parte 2 pronta para printar
    while (!done) //Espera o print acabar
    {
    }
    printf("Acabou cpu1\n");
    return 1;
}

int criar(int id)
{
    int i;
    for (i = 0; i < TAM; i++)
    {
       a[i] = i;
    }

    vetorCriado = 1;

    while (!done)
    {
    }

    return 1;
}

int print(int id)
{
    while (!vetorCriado) //Fica preso enquanto nao criou o vetor
    {
    }
    while (!flag || !flag2 || flagPrint < 2) //Fica esperando enquanto os cpus nao acabarem
    {
    }
    int i;
    printf("\n");

    printf("\n Print vetor\n");
    for (i = 0; i < TAM; i++)
    {
        printf("Graus = %d Rad %f\n", i , a[i]);
    }

    printf("\nAcabou print\n");

    done = 1;

    return 1;
}

int main(int argc, char **argv)
{
    int i;

    int id = impProcessorId();

    switch (id)
    {

    case 0:
        printf("CPU1 id=%d starting...\n", id);
        cpu1(id);
        break;

    case 1:
        printf("CPU0 id=%d starting...\n", id);
        cpu0(id);
        break;

    case 2:
        printf("CPU PRINT id=%d starting...\n", id);
        print(id);
        break;
    case 3:
        printf("CPU CRIAR id=%d starting...\n", id);
        criar(id);
        break;
    case 4:
        break;
    }

    return 1;
}
