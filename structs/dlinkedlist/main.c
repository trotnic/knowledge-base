#include <stdio.h>
#include "headers/list.h"

void print_data(void *data) {
    printf("%d\t", *((int *)data));
}

int main(int argc, char const *argv[])
{
    int values[10];
    for (size_t i = 0; i < 10; i++) {
        values[i] = rand() % 10 + 2;
        printf("%d\t", values[i]);
    }

    puts("");

    t_list *list;
    init(&list, values, sizeof(int), 10);


    delete_node(list, get_node_at(list, 5));
    printf("%d\n", *((int *)get_data_at(list, 5)));


    puts("");
    iterate(list, print_data);
    printf("\n%lu", count(list));

    return 0;
}
