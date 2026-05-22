using namespace std;

void bubbleSortAscending(unsigned int* arr, unsigned int* out, size_t n)
{
    unsigned int flag, temp = 0;

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
    for(size_t i = 0; i < n; i++) *(out + i) = *(arr + i);
}

void insertionSort(unsigned int* arr, unsigned int* out, size_t n)
{
    unsigned int key = 0, temp = 0;

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
    for(size_t i = 0; i < n; i++) *(out + i) = *(arr + i);
}
