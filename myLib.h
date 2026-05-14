#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define FIELD 50

void printMessage(char[]);
void printArray(int[], int);

int *initArray(int);

int *fillArrayBigInterval(int);
int *fillArraySmallInterval(int);

int *copyArray(int[], int);

int *bubbleSortAscending(int[], int);
int *bubbleSortDescending(int[], int);
int *insertionSort(int[], int);
