#include <stdio.h>
#include "../console.h"
#define SIZE 10

void bubbleSort(int array[], int size)
{
    for (int pass = 1; pass < size; ++pass) {
        int swapped = 0;
        for (int i = 0; i < size - pass; ++i) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main(void)
{
    use_utf8_console();
    int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    puts(u8"排序前");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d%c", a[i], i == SIZE - 1 ? '\n' : ' ');
    }
    bubbleSort(a, SIZE);
    puts(u8"排序後");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d%c", a[i], i == SIZE - 1 ? '\n' : ' ');
    }
    return 0;
}
