#include "path_linked_list.h"
#include <malloc.h>
#include <stddef.h>
#include <string.h>

void add_node(Node **root, const char *name, uint16_t name_len)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->name = name;
    new_node->next = NULL;
    new_node->name_len = name_len;
    if (*root == NULL)
    {
        *root = new_node;
        return;
    }
    Node *current = *root;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

void get_path(Node *root, char *output_string)
{
    Node *current = root;
    size_t current_byte = 0;
    while (current != NULL)
    {
        size_t len = current->name_len;
        memcpy(output_string + current_byte, current->name, len);
        current_byte += len;
        if (current->next != NULL)
        {
            output_string[current_byte] = '/';
            current_byte++;
        }
        current = current->next;
    }
    output_string[current_byte] = '\0';
}

void delete_last_node(Node **root)
{
    if (*root == NULL)
        return;
    if ((*root)->next == NULL)
    {
        free(*root);
        *root = NULL;
        return;
    }
    Node *current = *root;
    while (current->next->next != NULL)
        current = current->next;
    free(current->next);
    current->next = NULL;
}
