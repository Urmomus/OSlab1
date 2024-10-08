#if !defined(P_LINKED_LIST_H)
#define P_LINKED_LIST_H

#include <inttypes.h>

typedef struct Node
{
    const char *name;
    uint16_t name_len;
    struct Node *next;
} Node;
void add_node(Node **root, const char *name, uint16_t name_len);
void get_path(Node *root, char *output_string);
void delete_last_node(Node **root);

#endif // P_LINKED_LIST_H
