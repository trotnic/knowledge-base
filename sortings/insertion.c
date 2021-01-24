#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

void sort(int arr[], const int size);
void initialize(int arr[], const int size, const int lowerBound, const int upperBound);
void print_array(const int arr[], const int size);

int main(int argc, char const *argv[]) 
{
    const int size = 10;
    const int a = 10;
    const int b = 20;
    int arr[size];
    
    initialize(arr, size, a, b);
    print_array(arr, size);
    sort(arr, size);
    print_array(arr, size);
}

void print_array(const int arr[], const int size) 
{
    if (arr == NULL) {
        printf("LOL, you didn't pass an array to be printer in __%s__", __func__);
        return;
    }
    for (size_t i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    puts("");    
}

void initialize(int arr[], const int size, const int lowerBound, const int upperBound) 
{
    if (arr == NULL) {
        printf("LOL, you didn't pass an array to be initialized in __%s__", __func__);
        return;
    }    
    for (size_t i = 0; i < size; i++) 
        arr[i] = rand() % (upperBound - lowerBound) + lowerBound;
}

void sort(int arr[], const int size) 
{
    if (arr == NULL) {
        printf("LOL, you didn't pass an array to be sorted in __%s__", __func__);
        return;
    }
    for (size_t i = 0; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}