typedef struct Node {
    struct Node *next;
    struct Node *prev;

    void *data;

} Node;

typedef struct List {
    struct Node *_head;
    struct Node *_tail;
} List;


List* llist_init();
void llist_push(List* list, void *data, size_t size);
void llist_push_at(List* list, void *data, size_t size, int idx);
void llist_map(List* list, void (*map_func_ptr)(void *));
Node* llist_index(List *list, int idx);
void* llist_get(List *list, int idx);
void llist_delete(List *list, int idx);
int llist_len(List* list);

void llist_swap_data_ptrs(List* list, Node* a, Node* b);
void llist_sort(List* list, int (*cmp_func_ptr)(void*, void*));

