typedef enum { 
    HEAD, 
    TAIL, 
    MID 
} llist_node_type;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    llist_node_type type;

    void *data;

} Node;


struct Node* llist_init();
Node* llist_index(Node *current, int idx);
void llist_push(Node *current, void *data, size_t size);
void llist_pop(Node *current, int idx);
void llist_swap_nodes(Node* a, Node* b);
void llist_sort(Node *current, int (*cmp_func_ptr)(void*, void*));
void llist_map(Node *current, void (*map_func_ptr)(void *));
int llist_len(Node *current);