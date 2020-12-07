#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"

#define TAM 1024
//int a[TAM] = {10, 8, 5, 2, 3, 6, 7, 1, 4, 9, 13, 11, 12, 17, 15, 16, 14};

static volatile int a[TAM];
static volatile int flag = 0;
static volatile int flag2 = 0;
static volatile int vetorCriado = 0;
static volatile int flagPrint = 0;
static volatile int done = 0;

void mergeSort(int *vetor, int posicaoInicio, int posicaoFim)
{

    int i, j, k, metadeTamanho, *vetorTemp;
    if (posicaoInicio == posicaoFim)
        return;
    metadeTamanho = (posicaoInicio + posicaoFim) / 2;

    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *)malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while (i < metadeTamanho + 1 || j < posicaoFim + 1)
    {
        if (i == metadeTamanho + 1)
        {
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }
        else
        {
            if (j == posicaoFim + 1)
            {
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
            else
            {
                if (vetor[i] < vetor[j])
                {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                else
                {
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }
    }
    for (i = posicaoInicio; i <= posicaoFim; i++)
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
}

int cpu0(int id)
{
    
    while (!vetorCriado) //Fica preso enquanto nao criou o vetor
    {
    }

    mergeSort(&a, 0, TAM / 2);
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

    mergeSort(&a, (TAM / 2) + 1, TAM);
    flag2 = 1; //Parte 2 finalizada

    while (!flag) //Fica preso enquanto parte 1 nao acabou
    {
    }
    flagPrint++; //Parte 2 pronta para printar
    while (!done) //Espera o print acabar
    {
    }
    printf("Acabou cpu1\n");
    return 1;
}

int criar(int id)
{

    int i;

    printf("\n\n VETOR ORIGINAL \n");//Cria um vertor com numeros aleatorios
    for (i = 0; i < TAM / 2; i++)
    {
        a[i] = rand() % 2500;
        printf("%d ", a[i]);
    }
    for (i = TAM / 2; i < TAM; i++)
    {
        a[i] = (rand() % 5000) + 2500;
        printf("%d ", a[i]);
    }
    vetorCriado = 1;

    while (!done)
    {
    }

    return 1;
}

int print(int id)
{
    while (!vetorCriado)//Fica preso enquanto nao criou o vetor
    {
    }
    while (!flag || !flag2 || flagPrint < 2) //Fica esperando enquanto os cpus nao acabarem
    {
    }
    int i;
    printf("\n");

    printf("\n VETOR ORDENADO \n");
    for (i = 0; i < TAM; i++)
    {
        printf("%d ", a[i]);
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
