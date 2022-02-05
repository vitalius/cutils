#include <stdio.h>
#include <stdlib.h>
#include "llist.h"


/**
 * Initialize linked list
 */ 
struct Node* llist_init() {
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    struct Node *tail = (struct Node*) malloc(sizeof(struct Node));
    head->data = NULL;
    tail->data = NULL;

    head->next = tail;
    head->prev = NULL;
    head->type = HEAD;

    tail->next = NULL;
    tail->type = TAIL;
    tail->prev = head;

    return head;
}

/**
 * Find and return element at the index 'idx'
 */
Node* llist_index(Node *current, int idx) {
    if (idx < 1)
        idx = 1;

    // rewind back to the head of the list
    while (current->type != HEAD) {
        current = current->prev;
    }

    // index from head of the list
    int i = 1;
    while (current->type != TAIL && i <= idx) {
        current = current->next;
        i = i+1;
    }

    return current;
}

/**
 * Add list element to the head of the list
 */
void llist_push(Node *current, void *data, size_t size) {
    if (current == NULL) {
        return;
    }

    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }

    new_node->next = current->next;
    new_node->prev = current;
    new_node->type = MID;

    Node *ahead = current->next;
    ahead->prev = new_node;

    current->next = new_node;

    new_node->data = malloc(size);
    if (new_node->data == NULL) {
        return;
    }

    // copy data byte-by-byte
    int i;
    for(i=0; i<size; i++) {
        *(char*)(new_node->data +i) = *(char*)(data +i);
    }
}


/**
 * Remove list element at the index and free memory
 */
void llist_pop(Node *current, int idx) {
    Node* n = llist_index(current, idx);

    if (n == NULL || n->type != MID) {
        return;
    }

    Node* prev = n->prev;
    Node* next = n->next;
    prev->next = next;
    next->prev = prev;
    free(n->data);
    free(n);
}


/**
 * Swap node data
 */
void llist_swap_nodes(Node* a, Node* b) {
    if (a->type != MID || b->type != MID) {
        return;
    }

    struct Node tmp;
    tmp.data = a->data;
    a->data = b->data;
    b->data = tmp.data;
}


/**
 * Simple bubble sort
 */
void llist_sort(Node *current, int (*cmp_func_ptr)(void*, void*)) {
    Node* a = llist_index(current, 0);
    Node* b = llist_index(current, 0);

    while (a->type == MID) {
        b = llist_index(current, 0);
        while (b->type == MID) {
            if (a->data != NULL && b->data != NULL 
                    && 1 > (*cmp_func_ptr)(a->data, b->data)) {
                llist_swap_nodes(a, b);
            }
            b = b->next;
        }
        a = a->next;
    }
}


/**
 * Map function onto list data 
 */
void llist_map(Node *current, void (*map_func_ptr)(void *)) {
    Node* n = llist_index(current, 0);
    while (n->type == MID) {
        (*map_func_ptr)(n->data);
        n = n->next;
    }
}


/**
 * Returns the length of the list
 */
int llist_len(Node *current) {
    Node* n = llist_index(current, 0);

    int count = 0;
    while (n->type == MID) {
        count += 1;
        n = n->next;
    }

    return count;
}

