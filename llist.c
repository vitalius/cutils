#include <stdio.h>
#include <stdlib.h>
#include "llist.h"


/**
 * Initialize linked list
 */ 
List* llist_init() {
    List *list = (struct List*) malloc(sizeof(struct List));

    // special nodes for HEAD and TAIL of the list
    // these don't hold any data
    Node *head = (struct Node*) malloc(sizeof(struct Node));
    Node *tail = (struct Node*) malloc(sizeof(struct Node));

    if (list == NULL || head == NULL || tail == NULL) {
        return NULL;
    }

    head->data = NULL;
    tail->data = NULL;

    head->next = tail;
    head->prev = NULL;

    tail->next = NULL;
    tail->prev = head;

    list->_head = head;
    list->_tail = tail;

    return list;
}

/**
 * Find and return element at the index 'idx'
 */
Node* llist_index(List* list, int idx) {
    if (idx < 0)
        idx = 0;

    // index from head of the list
    int i = 0;
    Node* n = list->_head;
    while (n != list->_tail && i != idx) {
        n = n->next;
        i = i+1;
    }

    return n;
}

/**
 * Returns pointer to data at the index
 */
void* llist_get(List* list, int idx) {
    return llist_index(list, idx)->data;
}

/**
 * Add element to list after index 'idx'
 */
void llist_push_at(List *list, void *data, size_t size, int idx) {
    if (list == NULL) {
        return;
    }

    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }

    Node* current = llist_index(list, idx);

    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
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
 * Add list element to the head of the list
 */
void llist_push(List *list, void *data, size_t size) {
    llist_push_at(list, data, size, 0);
}


/**
 * Remove list element at the index and free memory
 */
void llist_delete(List* list, int idx) {
    Node* n = llist_index(list, idx);

    if (n == NULL || n == list->_head || n == list->_tail) {
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
void llist_swap_data_ptrs(List* list, Node* a, Node* b) {
    if (a == list->_head 
           || a == list->_tail 
           || a == b 
           || b == list->_head 
           || b == list->_tail) {
        return;
    }

    void* d_ptr = a->data;
    a->data = b->data;
    b->data = d_ptr;
}


/**
 * Simple bubble sort
 */
void llist_sort(List *list, int (*cmp_func_ptr)(void*, void*)) {
    Node* a = list->_head->next;
    Node* b = list->_head->next;

    while (a != list->_tail) {
        b = list->_head->next;
        while (b != list->_tail) {
            if (-1 == (*cmp_func_ptr)(a->data, b->data)) {
                llist_swap_data_ptrs(list, a, b);
            }
            b = b->next;
        }
        a = a->next;
    }
}


/**
 * Map function onto list data 
 */
void llist_map(List* list, void (*map_func_ptr)(void *)) {
    Node* n = list->_head->next;
    while (n != list->_tail) {
        (*map_func_ptr)(n->data);
        n = n->next;
    }
}


/**
 * Returns the length of the list
 */
int llist_len(List* list) {
    Node* n = list->_head->next;

    int count = 0;
    while (n != list->_tail) {
        count += 1;
        n = n->next;
    }

    return count;
}

