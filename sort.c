#include "myLib.h"

void printMessage(char message[])
{
    printf("%s", message);
}

void printArray(int arr[], int n)
{
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%10d", arr[i]);
    }
}

// Initialization array
int *initArray(int n)
{
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL)
    {
        printMessage("Array doesn't exit.");
        return 0;
    }
    return arr;
}

// Random array generation from big interval
int *fillArrayBigInterval(int n)
{
    int *arr1, rand_num = 0;
    arr1 = initArray(n);

    for (int i = 0; i < n; i++)
    {
        rand_num = -10000 + rand() % (10000 - (-10000) + 1);
        arr1[i] = rand_num;
    }
    printArray(arr1, n);
    return arr1;
}

// Random array generation from small interval
int *fillArraySmallInterval(int n)
{
    int *arr2, rand_num = 0;
    arr2 = initArray(n);

    for (int i = 0; i < n; i++)
    {
        rand_num = -100 + rand() % (100 - (-100) + 1);
        arr2[i] = rand_num;
    }
    printArray(arr2, n);
    return arr2;
}

// Create array copy
int *copyArray(int arr[], int n)
{
    int *arr_copy;
    arr_copy = initArray(n);

    for (int i = 0; i < n; i++)
    {
        arr_copy[i] = arr[i];
    }

    // printArray(arr_copy,n);
    return arr_copy;
}

// First sort method Bubble sort
int *bubbleSortAscending(int arr[], int n)
{
    int flag, temp = 0;

    for (int i = 0;; i++)
    {
        flag = 0;
        for (int j = n - 1; j > i; j--)
        {
            if (arr[j - 1] > arr[j])
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
    printArray(arr, n);
    return arr;
}

// Additional sort method  descending sort
int *bubbleSortDescending(int arr[], int n)
{
    int flag, temp = 0;

    for (int i = 0;; i++)
    {
        flag = 0;
        for (int j = n - 1; j > i; j--)
        {
            if (arr[j] > arr[j - 1])
            {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
    printArray(arr, n);
    return arr;
}

int *insertionSort(int arr[], int n)
{
    int key = 0, temp = 0;

    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (key < arr[j])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printArray(arr, n);
    return arr;
}

void printHeader(int n)
{
    printf("\n\nNumber of items %d      Big interval   |   Small interval", n);
    printf("\n");
    for (int i = 0; i < FIELD + 10; i++)
        printf("_");
    printf("\n");
}

void printItem(char mes[], double time_big, double time_small)
{
    printf("%s %21.3f  %18.3f", mes, time_big, time_small);
     printf("\n");
    for (int j = 0; j < FIELD  +10; j++)
        printf("_");
    printf("\n");
}

int main()
{
    int n = 0; // array size
    int *arr1, *arr2, *arrCopy1, *arrCopy2, *arrCopy3, *arrCopy4;
    int *arrBubble1, *arrBubble2, *arrInsert1, *arrInsert2;
    srand(time(NULL));

    do
    {
        printMessage("\nEnter array size->");
        scanf_s("%d", &n);
    } while (n <= 0);

    printMessage("\nInitial arrays generated.\n");
    arr1 = fillArrayBigInterval(n);
    arr2 = fillArraySmallInterval(n);

    printMessage("\nCopies of arrays created.\n");
    arrCopy1 = copyArray(arr1, n);
    arrCopy2 = copyArray(arr2, n);
    arrCopy3 = copyArray(arr1, n);
    arrCopy4 = copyArray(arr2, n);

    printMessage("\nBubble sorting done.\n");

    clock_t start_big_b = clock();
    arrBubble1 = bubbleSortAscending(arrCopy1, n);
    clock_t end_big_b = clock();
    double time_big_b = ((double)(end_big_b - start_big_b)) / CLOCKS_PER_SEC;

    clock_t start_small_b = clock();
    arrBubble2 = bubbleSortAscending(arrCopy2, n);
    clock_t end_small_b = clock();
    double time_small_b = ((double)(end_small_b - start_small_b)) / CLOCKS_PER_SEC;

    printMessage("\nInsert sorting done.\n");

    clock_t start_big_in = clock();
    arrInsert1 = insertionSort(arrCopy3, n);
    clock_t end_big_in = clock();
    double time_big_in = ((double)(end_big_in - start_big_in)) / CLOCKS_PER_SEC;

    clock_t start_small_in = clock();
    arrInsert2 = insertionSort(arrCopy4, n);
    clock_t end_small_in = clock();
    double time_small_in = ((double)(end_small_in - start_small_in)) / CLOCKS_PER_SEC;

    printHeader(n);
    printItem("Bubble sort", time_big_b, time_small_b);
    printItem("Insertion sort", time_big_in, time_small_in);
    return 0;
}