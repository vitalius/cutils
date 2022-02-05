#include <stdio.h>
#include "llist.h"


void print_node(void *data) {
    printf(" %d", *(int*)data);
}

int compare_node(void *a, void *b) {
    if (*(int*)a < *(int*)b) {
        return -1;
    } else if (*(int*)a > *(int*)b) {
        return 1;
    }
    return 0;
}



int main(int argc, char** argv) {
    Node* list = llist_init();
    int k = 17, i;

    for(i=0; i<k; i++) {
        llist_push(list, &i, sizeof(int));
    }
    llist_map(list, print_node);
    printf("\n");

    llist_sort(list, compare_node);
    
    llist_map(list, print_node);
    printf("\n");

    int llen = llist_len(list);
    printf("Size %d\n", llen);

    for(i=0; i<k; i++) {
        llist_pop(list, llen-i);
    }

    llist_map(list, print_node);
    printf("\n");
    printf("Size %d\n", llist_len(list));

    return 0;
}