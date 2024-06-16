#include "list.h"
#include <stdlib.h>

node *create_node(void *data)
{
    node *new = (node *) malloc(sizeof(node));
    if (new == NULL)
        HANDLE_ERR_V("NODE_MEM_ALLOC", "Memory allocation failed for node.");
    new->data = data;
    new->next = NULL;
    return new;
}

list *_list_init(size_t stride)
{
    list *new = (list *)malloc(sizeof(list));
    if (new == NULL)
        HANDLE_ERR_V("LIST_MEM_ALLOC", "Memory allocation failed for list.");
    new->head = NULL;
    new->stride = stride;
    new->len = 0;
    return new;
}

void list_destroy(list *l)
{
    if (l)
    {
        node *current = l->head;
        while (current != NULL)
        {
            node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(l);
}

int is_list_empty(list *l)
{
    return (l->head == NULL);
}

void list_append(list *l, void *data)
{
    node *new = create_node(data);
    if (is_list_empty(l))
    {
        l->head = new;
    }
    else 
    {
        node *current = l->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
    l->len++;
}

void list_prepend(list *l, void *data)
{
    node *new = create_node(data);
    if (is_list_empty(l))
    {
        l->head = new;
    }
    else 
    {
        node *temp = l->head;
        l->head = new;
        new->next = temp;
    }
    l->len++;
}

void list_remove(list *l, size_t idx)
{   
    // support for reverse indexing 
    if (idx < 0 || idx >= l->len)
        HANDLE_ERR_V("LIST_IDX_OUT_OF_BOUNDS", "index provided (%zu) is out of bounds of list (length: %zu)", idx, l->len);

    if (is_list_empty(l))
        HANDLE_ERR_V("LIST_EMPTY", "cannot delete from empty list");

    if (idx == 0)
    {
        // remove head
        node *temp = l->head;
        l->head = l->head->next;
        free(temp);
    }
    else
    {   
        node *current = l->head;
        node *prev = NULL, *temp = NULL;
        size_t t = 0;     // target index 
        while (current != NULL && t != idx)
        {
            prev = current;
            current = current->next;
            t++;
        }

        temp = current;
        prev->next = current->next;
        free(temp);
    }
    l->len--;
}

void *list_get(list *l, size_t idx)
{   
    if (idx < 0 || idx >= l->len)
        HANDLE_ERR_V("LIST_IDX_OUT_OF_BOUNDS", "index provided (%zu) is out of bounds of list (length: %zu)", idx, l->len);

    node *current = l->head;
    size_t t = 0;       // target index
    while (t != idx && current != NULL)
    {   
        current = current->next;
        t++;
    }
    return current->data;
}

void pop(list *l)
{
    list_remove(l, l->len - 1);
}

void list_print(list *l, void (*print_item)(void *))
{
    node *current = l->head;
    printf("[");
    while (current != NULL)
    {   
        print_item(current->data);
        if (current->next != NULL)
        {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}


void print_int(void *item)
{
    printf("%d", (item));
}

void print_str(void *item)
{
    printf("%s", (char *)item);
}


void test(void);
int main(void)
{   
    test();
    return 0;    
}   

void test(void)
{
    list *l = list_init(int);
    
    // appending ints 
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list_map_items(l, numbers);
    list_print(l, print_int);

    list_destroy(l);
}
