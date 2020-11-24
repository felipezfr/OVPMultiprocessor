#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"

#define NUM_VALUES 35

static volatile int flag = 0;
static volatile int flag2 = 0;
static volatile int fibResPar = 0;
static volatile int fibResImpar = 0;
int fib(int i)
{
    return (i > 1) ? fib(i - 1) + fib(i - 2) : i;
}

int par(int id)
{

    int i;

    for (i = 0; i < NUM_VALUES; i++)
    {

        int result = fib(i);
        while (flag) //flag == 1
        {
        }
        printf("CPU %d: fib(%d) = %d\n", id, i, result);
        fibResPar = result;
        flag = (i >= (NUM_VALUES - 1)) ? 2 : 1;
        i++;
    }

    while (flag)
    {
    }

    return 1;
}

int impar(int id)
{

    int j;

    for (j = 1; j < NUM_VALUES; j++)
    {

        int result = fib(j);
        while (flag2)
        {
        }
        printf("CPU %d: fib(%d) = %d\n", id, j, result);
        fibResImpar = result;
        flag2 = (j >= (NUM_VALUES - 1)) ? 2 : 1;
        j++;
    }

    while (flag2)
    {
    }

    return 1;
}

int print(int id)
{

    int done = 0;
    do
    {
        while (!flag)
        {
            if (flag == 2 || flag2 == 2)
                break;
        }
        printf("CPU %d: pritando 0 = %d\n", id, fibResPar);
        flag = 0;
        while (!flag2)
        {
            if (flag == 2 || flag2 == 2)
                break;
        }
        printf("CPU %d: pritando 1 = %d\n", id, fibResImpar);
        flag2 = 0;

        if (flag == 2 || flag2 == 2)
            done = 1;
    } while (!done);

    return 1;
}

int main(int argc, char **argv)
{

    int id = impProcessorId();

    switch (id)
    {

    case 0:
        printf("CPU PRINT id=%d starting...\n", id);
        print(id);
        break;

    case 1:
        printf("CPU IMPAR id=%d starting...\n", id);
        impar(id);
        break;

    case 2:
        printf("CPU PAR id=%d starting...\n", id);
        par(id);
        break;
    case 3:
        break;
    }

    return 1;
}
