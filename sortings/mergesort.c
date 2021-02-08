#include <stdlib.h>
#include <stdio.h>


    /*
    * i            j
    * 1 2 3        2 5 9
    *   
    *      1
    *   i          j
    * 1 2 3        2 5 9
    * 
    *      1 2
    * 
    *     i        j
    * 1 2 3        2 5 9
    * 
    *      1 2 2
    * 
    *     i          j
    * 1 2 3        2 5 9
    * 
    *      1 2 2 3
    * 
    *       i        j
    * 1 2 3 _      2 5 9
    * 
    *      1 2 2 3 5
    * 
    *       i          j
    * 1 2 3 _      2 5 9
    * 
    *      1 2 2 3 5 9
    * 
    *       i            j
    * 1 2 3 _      2 5 9 _
    * 
    * 
    * рекурсивная природа сортировки слиянием
    * и принцип "разделяй и властвуй" будут всегда гарантировать
    * что подмассивы будут отсортированы и не будет "забытых" значений
    * 
    * (то есть ситуации, вроде {1,2,3} и {5,2,1}, исключаются; 
    *  очевидно, что здесь при обходе значения 2,1 будут не на своих местах)
    * 
    */

void merge(int arr[], const int p, const int q, const int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int *l_arr = malloc(sizeof(int) * (n1 + 1));
    int *r_arr = malloc(sizeof(int) * (n2 + 1));
    for (int i = 0; i < n1; i++) l_arr[i] = arr[p + i];
    for (int i = 0; i < n2; i++) r_arr[i] = arr[q + i + 1];
    l_arr[n1] = 9999999;
    r_arr[n2] = 9999999;
    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (l_arr[i] <= r_arr[j]) {
            arr[k] = l_arr[i];
            i++;
        } else {
            arr[k] = r_arr[j];
            j++;
        }
    }
}

void merge_sort(int arr[], const int p, const int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

int main(int argc, char const *argv[])
{
    int arr[20];
    for (int i = 0; i < 20; i++) arr[i] = rand() % 20;
    for (size_t i = 0; i < 20; i++) printf("\t%d", arr[i]);
    puts("");
    merge_sort(arr, 0, 19);
    for (size_t i = 0; i < 20; i++) printf("\t%d", arr[i]);
    
    return 0;
}
